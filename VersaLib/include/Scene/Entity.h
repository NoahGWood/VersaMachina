#pragma once
#include "Scene/Scene.h"
#include <entt.hpp>

namespace VersaMachina
{
    namespace Scenes
    {
        class Entity
        {
            public:
                Entity() = default;
                Entity(entt::entity handle, Scene* scene);
                Entity(const Entity& other) = default;
                ~Entity(){}

                template<typename T, typename... Args>
                T& AddComponent(Args&&... args)
                {
                    VM_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
                    return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
                }
                template<typename T>
                T& GetComponent()
                {
                    VM_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
                    return m_Scene->m_Registry.get<T>(m_EntityHandle);
                }
                template<typename T>
                bool HasComponent()
                {
                    return m_Scene->m_Registry.has<T>(m_EntityHandle);
                }
                template<typename T>
                void RemoveComponent()
                {
                    VM_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
                    m_Scene->m_Registry.remove<T>(m_EntityHandle);
                }

                operator bool() const { return (int)m_EntityHandle != 0; }
            private:
                entt::entity m_EntityHandle{0};
                Scene* m_Scene=nullptr;

        };
    } // namespace Scenes
    
} // namespace VersaMachina
