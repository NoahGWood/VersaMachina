#include "pch.h"
#include "Scene/SceneSerializer.h"


namespace VersaMachina
{
    namespace Scenes
    {
        SceneSerializer::SceneSerializer(const Ref<Scene>&scene)
            : m_Scene(scene) { }

        void SceneSerializer::Serialize(const std::string& filepath)
        {

        }
        void SceneSerializer::SerializeRuntime(const std::string& filepath)
        {
            VM_CORE_ASSERT(false, "Runtime Scene Serialization Not Implemented.");
        }
        bool SceneSerializer::Deserialize(const std::string& filepath)
        {

        }
        bool SceneSerializer::DeserializeRuntime(const std::string& filepath)
        {
            VM_CORE_ASSERT(false, "Runtime Scene Deserialization Not Implemented.");
            return false;
        }
    } // namespace Scenes
    
} // namespace VersaMachina
