#include "pch.h"
#include "Scene/Entity.h"

namespace VersaMachina
{
    namespace Scenes
    {
        Entity::Entity(entt::entity handle, Scene* scene)
            : m_EntityHandle(handle), m_Scene(scene) {}
    } // namespace Scene
    
} // namespace VersaMachina
