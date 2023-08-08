#pragma once
#include "Scene/Entity.h"

namespace VersaMachina
{
    namespace Scenes
    {
        class ScriptableEntity
        {
            public:
                virtual ~ScriptableEntity(){}
    
                template<typename T>
                T& GetComponent()
                {
                    return m_Entity.GetComponent<T>();
                }
                template<typename T>
                bool HasComponent()
                {
                    return m_Entity.HasComponent<T>();
                }
            protected:
                virtual void OnCreate() {}
                virtual void OnDestroy() {}
                virtual void OnUpdate(Timestep ts) {}

            private:
                Entity m_Entity;
                friend class Scene;
        };
    } // namespace Scenes
    
} // namespace VersaMachina
