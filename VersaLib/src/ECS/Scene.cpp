#include "pch.h"
#include "ECS/Scene.h"
#include "ECS/Components.h"
#include "Render/Renderer2D.h"
#include "ECS/Entity.h"
#include "ECS/ScriptableEntity.h"

namespace VersaMachina
{
    namespace ECS
    {

        Scene::Scene()
        {
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
        void Scene::DestroyEntity(Entity entity)
        {
            m_Registry.destroy(entity);
        }
        void Scene::OnUpdate(Timestep ts)
        {
        }
        void Scene::OnUpdateEditor(Timestep ts, Camera::EditorCamera& camera)
        {
            camera.OnUpdate(ts);
            VersaMachina::Render::Renderer2D::BeginScene(camera); // camera, lights, environment);
            DrawSprites();
            VersaMachina::Render::Renderer2D::EndScene();
        }
        void Scene::OnUpdateRuntime(Timestep ts)
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
            auto view = m_Registry.view<CameraComponent, TransformComponent>();
            Camera::Camera* mainCamera = nullptr;
    		for (auto entity : view)
    		{
                auto[camera, transform] = view.get<CameraComponent, TransformComponent>(entity);
                camera.m_Camera->SetTransform(transform.GetTransform());
                if(camera.Primary)
                {
                    mainCamera = camera.m_Camera;
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
//            	Render::Renderer2D::DrawQua(transform.GetTransform(), {0,0,0}, sprite.Color, {1,1}, {0,0,0}, sprite.Texture, 1.0f);
                Render::Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
            }
        }
        Entity Scene::GetPrimaryCamera()
        {
            auto view = m_Registry.view<CameraComponent>();
            for(auto entity : view)
            {
                auto camera = view.get<CameraComponent>(entity);
                if(camera.Primary)
                    return Entity{entity, this};
            }
            return {};
        }
        void Scene::OnViewportResize(uint32_t width, uint32_t height)
        {
            m_ViewportWidth = width;
            m_ViewportHeight = height;

            // Resize non-FixedAspectRatio cameras
            auto view = m_Registry.view<CameraComponent>();
    		for (auto entity : view)
    		{
                auto& camera = view.get<CameraComponent>(entity).m_Camera;
                if(camera)
                {
                    if(!camera->GetFixedAspectRatio())
                    {
                        camera->Resize(width, height);
                    }
                }
    		}
        }


        template<typename T>
        void Scene::OnComponentAdded(Entity entity, T& component)
        {
            VM_ASSERT(false, "No template provided for Scene::OnComponentAdded!")
        }

        template<>
        void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component) { }

        template<>
        void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component) { }

        template<>
        void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component) { }

        template<>
        void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
        {
            if(m_ViewportHeight > 0 && m_ViewportWidth > 0)
                component.m_Camera->Resize(m_ViewportWidth, m_ViewportHeight);
        }

        template<>
        void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component) { }
    } // namespace ECS
    
} // namespace VersaMachina
