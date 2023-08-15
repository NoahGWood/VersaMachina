#include "Versa.h"
#include "panels/SceneHierarchyPanel.h"

namespace VersaMachina
{
    class InspectorPanel
    {
        public:
            InspectorPanel() = default;
            InspectorPanel(const Ref<ECS::Scene>& scene, const Ref<ECS::Entity>& entity);

            void SetContext(const Ref<ECS::Scene>& context, const Ref<ECS::Entity>& entity);

            void OnImGuiRender();
            void DrawComponents();
        private:
            Ref<ECS::Scene> m_Context;
            Ref<ECS::Entity> m_SelectedEntity;
    };
} // namespace VersaMachina
