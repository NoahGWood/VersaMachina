#include "pch.h"
#include "panels/InspectorPanel.h"
#include "ECS/Components.h"
#include "ECS/ComponentUI.h"

namespace VersaMachina
{
    InspectorPanel::InspectorPanel(const Ref<ECS::Scene>& scene, const Ref<ECS::Entity>& entity)
    {
        SetContext(scene, entity);
    }
    void InspectorPanel::SetContext(const Ref<ECS::Scene>& context, const Ref<ECS::Entity>& entity)
    {
        m_Context = context;
        m_SelectedEntity = entity;
    }

    void InspectorPanel::OnImGuiRender()
    {
        ImGui::Begin("Inspector");
        {
            if (m_SelectedEntity && *m_SelectedEntity)
                DrawComponents();
        }
        ImGui::End();
    }

    void InspectorPanel::DrawComponents()
    {   
        bool removeComponent = false;
        const ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_SpanAvailWidth;

        ECS::DrawComponent<ECS::TagComponent>(*m_SelectedEntity);

        ImGui::SameLine();
        ImGui::PushItemWidth(-1);

        if (ImGui::Button("Add Component"))
            ImGui::OpenPopup("AddComponent");
        
        if (ImGui::BeginPopup("AddComponent"))
        {
            if (!m_SelectedEntity->HasComponent<ECS::CameraComponent>())
            {
                if (ImGui::MenuItem("Camera"))
                {
                    m_SelectedEntity->AddComponent<ECS::CameraComponent>();
                    ImGui::CloseCurrentPopup();
                }
            }
            if (!m_SelectedEntity->HasComponent<ECS::SpriteRendererComponent>())
            {
                if (ImGui::MenuItem("Sprite Renderer"))
                {
                    m_SelectedEntity->AddComponent<ECS::SpriteRendererComponent>();
                    ImGui::CloseCurrentPopup();
                }
            }
            ImGui::EndPopup();
        }
        ImGui::PopItemWidth();
        ECS::DrawComponent<ECS::TransformComponent>(*m_SelectedEntity);
        ECS::DrawComponent<ECS::SpriteRendererComponent>(*m_SelectedEntity);
        ECS::DrawComponent<ECS::CameraComponent>(*m_SelectedEntity);
    }

} // namespace VersaMachina
