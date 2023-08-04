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

            private:
                entt::registry m_Registry;
        };

    } // namespace Scenes
    
} // namespace VersaMachina
