#include "pch.h"
#include "Scene/Scene.h"
#include "Scene/Components.h"
#include "Render/Renderer2D.h"
#include "Scene/Entity.h"
#include "Scene/ScriptableEntity.h"

namespace VersaMachina
{
    namespace Scenes
    {

        Scene::Scene()
        {
//            entt::entity entity = m_Registry.create();
        }
        Scene::~Scene()
        {
            
        }
        Entity Scene::CreateEntity(const std::string& name)
        {
            Entity entity = { m_Registry.create(), this};
            entity.AddComponent<TransformComponent>();
            auto& tag = entity.AddComponent<TagComponent>();
            if(name.empty())
            {
                tag.Tag = "Unnamed Entity";
            } else {
                tag.Tag = name;
            }
            return entity;
        }
        void Scene::OnUpdate(Timestep ts)
        {
            // Update scripts
            {
                auto view = m_Registry.view<NativeScriptComponent>();
                for(auto entity : view) 
                {
                    auto& nsc = view.get<NativeScriptComponent>(entity);
                    if(!nsc.Instance)
                    {
                        VM_CORE_INFO("Script not instantiated, creating");
                        nsc.Instance = nsc.InstantiateScript();
                        nsc.Instance->m_Entity = Entity{entity,this};
                        nsc.Instance->OnCreate();
                    }
                    nsc.Instance->OnUpdate(ts);
                }
            }

            // Render Scene
            auto view = m_Registry.view<TransformComponent, CameraComponent>();
            Camera::Camera* mainCamera = nullptr;
    		for (auto entity : view)
    		{
                auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
                if(camera.Primary)
                {
                    mainCamera = camera.m_Camera;
                    camera.m_Camera->SetTransform(transform.Transform);
                    break;
                }
    		}
            if(mainCamera)
            {
                VersaMachina::Render::Renderer2D::BeginScene(mainCamera); // camera, lights, environment);
                DrawSprites();
                VersaMachina::Render::Renderer2D::EndScene();
            }
        }
        void Scene::DrawSprites()
        {
            auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
            for (auto entity : group)
            {
                auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
//                auto& sprite = group.get<SpriteRendererComponent>(entity);
            	Render::Renderer2D::DrawQuad(transform, {0,0,0}, sprite.Color, {1,1}, {0,0,0}, sprite.Texture, 1.0f);
            }
        }
        void Scene::OnViewportResize(uint32_t width, uint32_t height)
        {
            m_ViewportWidth = width;
            m_ViewportHeight = height;

            // Resize non-FixedAspectRatio cameras
            auto view = m_Registry.view<CameraComponent>();
            Camera::Camera* mainCamera = nullptr;
    		for (auto entity : view)
    		{
                auto& camera = view.get<CameraComponent>(entity).m_Camera;
                if(!camera->GetSettings()->FixedAspectRatio)
                {
                    camera->Resize(width, height);
                }
    		}
        }
    } // namespace Scenes
    
} // namespace VersaMachina
