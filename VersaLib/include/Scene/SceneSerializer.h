#pragma once
#include "Core/Base.h"
#include "Scene/Scene.h"

namespace VersaMachina
{
    namespace Scenes
    {
        class SceneSerializer
        {
            public:
                SceneSerializer(const Ref<Scene>&scene);

                void Serialize(const std::string& filepath);
                void SerializeRuntime(const std::string& filepath);

                bool Deserialize(const std::string& filepath);
                bool DeserializeRuntime(const std::string& filepath);

            private:
                Ref<Scene> m_Scene;
        };
    } // namespace Scenes
    
} // namespace VersaMachina
