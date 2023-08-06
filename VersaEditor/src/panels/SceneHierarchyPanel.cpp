#include "panels/SceneHierarchyPanel.h"

#include <imgui/imgui.h>

namespace VersaMachina
{
    SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scenes::Scene>& context)
    {
        SetContext(context);
    }

    void SceneHierarchyPanel::SetContext(const Ref<Scenes::Scene>& context)
    {
        m_Context = context;
    }

    void SceneHierarchyPanel::OnImGuiRender()
    {
        ImGui::Begin("Scene Hierarchy");
        m_Context->m_Registry.each([&](auto entityID)
        {
            Scenes::Entity entity{entityID, m_Context.get() };
            DrawEntityNode(entity);
        });

        if(ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
        {
            m_SelectedEntity = {};
        }

        ImGui::End();
        ImGui::Begin("Inspector");
        if(m_SelectedEntity)
        {
            DrawComponents(m_SelectedEntity);
        }
        ImGui::End();
    }
    void SceneHierarchyPanel::DrawEntityNode(Scenes::Entity entity)
    {
        std::string& tag = entity.GetComponent<Scenes::TagComponent>().Tag;

        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;

        if(m_SelectedEntity == entity)
        {
            flags =  ImGuiTreeNodeFlags_Selected | flags;
        }

        bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
        if(ImGui::IsItemClicked())
        {
            m_SelectedEntity = entity;
        }
        if(opened)
        {
            ImGui::TreePop();
        }
    }

    void SceneHierarchyPanel::DrawComponents(Scenes::Entity entity)
    {
        if(entity.HasComponent<Scenes::TagComponent>())
        {
            std::string& tag = entity.GetComponent<Scenes::TagComponent>().Tag;
            char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            strcpy(buffer, tag.c_str());
            if(ImGui::InputText("Tag", buffer, sizeof(buffer)))
            {
                tag = std::string(buffer);
            }
        }
        if(entity.HasComponent<Scenes::TransformComponent>())
        {
            if(ImGui::TreeNodeEx((void*)typeid(Scenes::TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
            {
                glm::mat4 transform = entity.GetComponent<Scenes::TransformComponent>().Transform;
                ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.01f);
    
                ImGui::TreePop();
            }
        }
    }
} // namespace VersaMachina