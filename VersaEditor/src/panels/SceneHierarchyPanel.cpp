#include "panels/SceneHierarchyPanel.h"
#include "ECS/ComponentUI.h"

namespace VersaMachina
{

    SceneHierarchyPanel::SceneHierarchyPanel(const Ref<ECS::Scene>& scene, const Ref<ECS::Entity>& entity)
    {
        SetContext(scene, entity);
    }

    void SceneHierarchyPanel::SetContext(const Ref<ECS::Scene>& context, const Ref<ECS::Entity>& entity)
    {
        m_Context = context;
        m_SelectedEntity = entity;
    }

    void SceneHierarchyPanel::OnImGuiRender()
    {
        ImGui::Begin("Scene Hierarchy");
        m_Context->m_Registry.each([&](auto entityID)
        {
            ECS::Entity entity{entityID, m_Context.get() };
            ECS::DrawEntityNode(entity, *m_Context, *m_SelectedEntity);
        });

        if(ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
        {
            VM_CORE_INFO("Hierarchy mouse down");
            *m_SelectedEntity = {};
        }
        if(ImGui::BeginPopupContextWindow(0,ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems))
        {
            if(ImGui::MenuItem("Create Empty Entity"))
                m_Context->CreateEntity("Empty Entity");
            ImGui::EndPopup();
        }
        ImGui::End();
    }
} // namespace VersaMachina