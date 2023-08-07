#pragma once
#include "Core/Timestep.h"
#include <entt.hpp>

namespace VersaMachina
{
    namespace Scenes
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
                void OnViewportResize(uint32_t width, uint32_t height);
                void DrawSprites();
                
                entt::registry m_Registry;
                uint32_t m_ViewportWidth=0, m_ViewportHeight=0;
            private:
                friend class Entity;
    
                template<typename T>
                void OnComponentAdded(Entity entity, T& component);
        };

    } // namespace Scenes
    
} // namespace VersaMachina
