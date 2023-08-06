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
            friend class Entity;
            
            public:
                Scene();
                ~Scene();

                Entity CreateEntity(const std::string& name="");

                void OnUpdate(Timestep ts);
                void OnViewportResize(uint32_t width, uint32_t height);
                void DrawSprites();
            private:
                entt::registry m_Registry;
                uint32_t m_ViewportWidth=0, m_ViewportHeight=0;
        };

    } // namespace Scenes
    
} // namespace VersaMachina
