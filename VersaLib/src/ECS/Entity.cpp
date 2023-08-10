#include "pch.h"
#include "ECS/Entity.h"

namespace VersaMachina
{
    namespace ECS
    {
        Entity::Entity(entt::entity handle, Scene* scene)
            : m_EntityHandle(handle), m_Scene(scene) {}
    } // namespace ECS
    
} // namespace VersaMachina
