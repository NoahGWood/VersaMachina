#pragma once

#include "Versa.h"

namespace VersaMachina
{
    class SceneHierarchyPanel
    {
        public:
            SceneHierarchyPanel() = default;
            SceneHierarchyPanel(const Ref<Scenes::Scene>& scene);

            void SetContext(const Ref<Scenes::Scene>& scene);

            void OnImGuiRender();
        private:
            void DrawEntityNode(Scenes::Entity entity);
            void DrawComponents(Scenes::Entity entity);
        private:
            Ref<Scenes::Scene> m_Context;
            Scenes::Entity m_SelectedEntity;

    };    
    static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float colWidth = 100.0f);
} // namespace VersaMachina
