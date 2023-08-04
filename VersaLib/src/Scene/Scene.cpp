#include "pch.h"
#include "Scene/Scene.h"
#include "Scene/Components.h"
#include "Render/Renderer2D.h"
#include "Scene/Entity.h"

namespace VersaMachina
{
    namespace Scenes
    {

        Scene::Scene()
        {
            entt::entity entity = m_Registry.create();
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
            // Render Scene
            auto group = m_Registry.view<TransformComponent, CameraComponent>();
            Camera::Camera* mainCamera = nullptr;
    		for (auto entity : group)
    		{
                auto& camera = group.get<CameraComponent>(entity);
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
                auto& transform = group.get<TransformComponent>(entity);
                auto& sprite = group.get<SpriteRendererComponent>(entity);
            	Render::Renderer2D::DrawQuad(transform, {0,0,0}, sprite.Color);
            }
        }
    } // namespace Scenes
    
} // namespace VersaMachina
