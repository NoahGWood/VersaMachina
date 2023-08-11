#pragma once

#include "Versa.h"

namespace VersaMachina
{
    class SceneHierarchyPanel
    {
        public:
            SceneHierarchyPanel() = default;
            SceneHierarchyPanel(const Ref<ECS::Scene>& scene);

            void SetContext(const Ref<ECS::Scene>& scene);

            void OnImGuiRender();
            ECS::Entity GetSelectedEntity() const { return m_SelectedEntity; }
        private:
            void DrawEntityNode(ECS::Entity entity);
            void DrawComponents(ECS::Entity entity);
        private:
            Ref<ECS::Scene> m_Context;
            ECS::Entity m_SelectedEntity;

    };    
    static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float colWidth = 100.0f);
} // namespace VersaMachina
