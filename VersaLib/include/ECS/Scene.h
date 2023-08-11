#pragma once
#include "Core/Timestep.h"
#include "Camera/EditorCamera.h"
#include <entt.hpp>

namespace VersaMachina
{
    namespace ECS
    {
        class Entity;

        class Scene
        {
            
            public:
                Scene();
                ~Scene();

                Entity CreateEntity(const std::string& name="");
                void DestroyEntity(Entity entity);

                void OnUpdate(Timestep ts);
                void OnUpdateEditor(Timestep ts, Camera::EditorCamera& camera);
                void OnUpdateRuntime(Timestep ts);

                void OnViewportResize(uint32_t width, uint32_t height);
                void DrawSprites();
                Entity GetPrimaryCamera();
                
                entt::registry m_Registry;
                uint32_t m_ViewportWidth=0, m_ViewportHeight=0;
            private:
                friend class Entity;
                friend class SceneSerializer;
                template<typename T>
                void OnComponentAdded(Entity entity, T& component);
        };

    } // namespace ECS
    
} // namespace VersaMachina
