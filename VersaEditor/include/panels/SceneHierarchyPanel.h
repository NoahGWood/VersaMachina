#pragma once

#include "Versa.h"

namespace VersaMachina
{
    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel() = default;
        SceneHierarchyPanel(const Ref<ECS::Scene>& scene, const Ref<ECS::Entity>& entity);

        void SetContext(const Ref<ECS::Scene>& scene, const Ref<ECS::Entity>& entity);

        void OnImGuiRender();
        
    private:
        Ref<ECS::Scene> m_Context;
        Ref<ECS::Entity> m_SelectedEntity;
    };
} // namespace VersaMachina
