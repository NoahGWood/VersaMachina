#pragma once
#include "ECS/Components.h"

namespace VersaMachina
{
    namespace ECS
    {
        // ImGui Special Controls
        void DrawVec3Control(const std::string &label, glm::vec3 &values, float resetValue = 0.0f, float colWidth = 100.0f);

        // Draw Entity Node
        void DrawEntityNode(Entity& entity, Scene& scene, Entity& selected);
        // Draw Component UI
        template <typename T, typename UIFunction>
        static void DrawComponentUI(const std::string &name, Entity& entity, UIFunction uiFunction, bool removable = true);

        template <typename T>
        void DrawComponent(Entity& e)
        {
            VM_ASSERT(false, "No template provided for ECS::DrawComponent!");
        }
        template <>
        void DrawComponent<TagComponent>(Entity& e);
        template <>
        void DrawComponent<TransformComponent>(Entity& e);
        template <>
        void DrawComponent<SpriteRendererComponent>(Entity& e);
        template <>
        void DrawComponent<CameraComponent>(Entity& e);
        template <>
        void DrawComponent<NativeScriptComponent>(Entity& e);
        template <>
        void DrawComponent<ScriptComponent>(Entity& e);
        // Draw Component Settings

        // Draw AddComponent Popup
    } // namespace ECS

} // namespace VersaMachina
