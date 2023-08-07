#include "panels/SceneHierarchyPanel.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

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
        if(ImGui::BeginPopupContextWindow(0,ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems))
        {
            if(ImGui::MenuItem("Create Empty Entity"))
                m_Context->CreateEntity("Empty Entity");
            ImGui::EndPopup();
        }
        ImGui::End();
        ImGui::Begin("Inspector");
        if(m_SelectedEntity)
        {
            DrawComponents(m_SelectedEntity);

            if(ImGui::Button("Add Component"))
                ImGui::OpenPopup("AddComponent");

            if(ImGui::BeginPopup("AddComponent"))
            {
                if(ImGui::MenuItem("Camera"))
                {
                    m_SelectedEntity.AddComponent<Scenes::CameraComponent>();
                    ImGui::CloseCurrentPopup();    
                }
                if(ImGui::MenuItem("Sprite Renderer"))
                {
                    m_SelectedEntity.AddComponent<Scenes::SpriteRendererComponent>();
                    ImGui::CloseCurrentPopup();    
                }
                ImGui::EndPopup();
            }
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
        bool entityDeleted = false;
        if(ImGui::BeginPopupContextItem())
        {
            if(ImGui::MenuItem("Delete Entity"))
            {
                entityDeleted = true;
            }
            ImGui::EndPopup();
        }
        if(opened)
        {
            ImGui::TreePop();
        }
        if(entityDeleted)
        {
            m_Context->DestroyEntity(entity);
            if(m_SelectedEntity == entity)
                m_SelectedEntity = {};
        }
    }

    void SceneHierarchyPanel::DrawComponents(Scenes::Entity entity)
    {
        bool removeComponent = false;
        const ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap; 

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
            if(ImGui::TreeNodeEx((void*)typeid(Scenes::TransformComponent).hash_code(), treeFlags, "Transform"))
            {
                auto& tc = entity.GetComponent<Scenes::TransformComponent>();
                DrawVec3Control("Position", tc.Translation);
                glm::vec3 rotation = glm::degrees(tc.Rotation);
                DrawVec3Control("Rotation", rotation);
                tc.Rotation = glm::radians(rotation);
                DrawVec3Control("Scale", tc.Scale, 1.0f);
                
                ImGui::TreePop();
            }
        }
        if(entity.HasComponent<Scenes::CameraComponent>())
        {
            if(ImGui::TreeNodeEx((void*)typeid(Scenes::CameraComponent).hash_code(), treeFlags, "Camera"))
            {
				auto& cameraComponent = entity.GetComponent<Scenes::CameraComponent>();
				auto& camera = cameraComponent.m_Camera;

                const char* projectionTypeStrings[] = { "Orthographic", "Perspective" };
				const char* currentProjectionTypeString = projectionTypeStrings[(int)camera->GetType()];
                if(ImGui::BeginCombo("Camera Type", currentProjectionTypeString))
                {
                    for(int i=0; i<2; i++)
                    {
                        bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
                        if(ImGui::Selectable(projectionTypeStrings[i], isSelected))
                        {
                            currentProjectionTypeString = projectionTypeStrings[i];
                            camera->SetType((Camera::CameraType)i);
                        }

                        if(isSelected)
                            ImGui::SetItemDefaultFocus();
                    }

                    ImGui::EndCombo();
                }
				ImGui::Checkbox("Primary", &cameraComponent.Primary);

                // Viewport
                glm::vec4 vp = camera->GetViewport();
                float viewport[4] = {vp[0], vp[1], vp[2], vp[3]};

                if(ImGui::DragFloat4("Viewport", viewport))
                {
                    vp = {viewport[0], viewport[1], viewport[2], viewport[3] };
                    camera->SetViewport(vp);
                }
                // Field of View
                const char* fovAxisStrings[] = { "Vertical", "Horizontal" };
                const char* currentFOVAxis = fovAxisStrings[(int)camera->GetFOVAxis()];
                if(ImGui::BeginCombo("FOV Axis", currentFOVAxis))
                {
                    for(int i=0; i<2; i++)
                    {
                        bool isSelected = currentFOVAxis == fovAxisStrings[i];
                        if(ImGui::Selectable(fovAxisStrings[i], isSelected))
                        {
                            currentFOVAxis = fovAxisStrings[i];
                            camera->SetFOVAxis((Camera::FOVAxis)i);
                        }
                        if(isSelected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
                float fov = camera->GetFOV();
                if(ImGui::DragFloat("Field of View", &fov))
                    camera->SetFOV(fov);
                // Aspect ratio
                float ar = camera->GetAspectRatio();
                if(ImGui::DragFloat("Aspect Ratio", &ar))
                    camera->SetAspectRatio(ar);
                bool fixed = camera->GetFixedAspectRatio();
                if(ImGui::Checkbox("Fixed Aspect Ratio",&fixed))
                    camera->SetFixedAspectRatio(fixed);
                // Clipping
                float clip[2] = { camera->GetNearClip(), camera->GetFarClip() };
                if(ImGui::DragFloat2("Clipping", clip))
                {
                    camera->SetNearClip(clip[0]);
                    camera->SetFarClip(clip[1]);
                }
                // Movement
                float zoomLevel = camera->GetZoomLevel();
                if(ImGui::DragFloat("Zoom", &zoomLevel))
                    camera->SetZoomLevel(zoomLevel);
                float moveSpeed = camera->GetMoveSpeed();
                if(ImGui::DragFloat("Move Speed", &moveSpeed))
                    camera->SetMoveSpeed(moveSpeed);
                float rotateSpeed = camera->GetRotateSpeed();
                if(ImGui::DragFloat("Rotate Speed", &rotateSpeed))
                    camera->SetRotateSpeed(rotateSpeed);
                ImGui::TreePop();
            }
        }
        if(entity.HasComponent<Scenes::SpriteRendererComponent>())
        {
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{4,4});
            bool open = ImGui::TreeNodeEx((void*)typeid(Scenes::SpriteRendererComponent).hash_code(), treeFlags, "Sprite Renderer");
            ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
            if(ImGui::Button("+", ImVec2{20,20}))
            {
                ImGui::OpenPopup("ComponentSettings");
            }
            ImGui::PopStyleVar();
            if(ImGui::BeginPopup("ComponentSettings"))
            {
                if(ImGui::MenuItem("Remove Component"))
                    removeComponent = true;
                ImGui::EndPopup();
            }
            if(open)
            {
                auto& src = entity.GetComponent<Scenes::SpriteRendererComponent>();
                ImGui::ColorEdit4("Color", glm::value_ptr(src.Color));
                ImGui::TreePop();
            }


            if(removeComponent == true)
                entity.RemoveComponent<Scenes::SpriteRendererComponent>();
        }
    }
    static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue, float colWidth)
    {
        ImGui::PushID(label.c_str());

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, colWidth);
        ImGui::Text(label.c_str());
        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0,0));
        
        float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.9f, 0.2f, 0.2f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});

        if(ImGui::Button("X", buttonSize))
            values.x = resetValue;
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##X", &values.x, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.3f, 0.8f, 0.3f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
        if(ImGui::Button("Y", buttonSize))
            values.y = resetValue;
        ImGui::PopStyleColor(3);
      
        ImGui::SameLine();
        ImGui::DragFloat("##Y", &values.y, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.2f, 0.25f, 0.8f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.2f, 0.35f, 0.9f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.2f, 0.25f, 0.8f, 1.0f});
        if(ImGui::Button("Z", buttonSize))
            values.z = resetValue;
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##Z", &values.z, 0.1f);
        ImGui::PopItemWidth();

        ImGui::PopStyleVar();

        ImGui::Columns(1);
                    
        ImGui::PopID();
    }

} // namespace VersaMachina