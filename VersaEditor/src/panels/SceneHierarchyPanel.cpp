#include "panels/SceneHierarchyPanel.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

namespace VersaMachina
{
    SceneHierarchyPanel::SceneHierarchyPanel(const Ref<ECS::Scene>& context)
    {
        SetContext(context);
    }

    void SceneHierarchyPanel::SetContext(const Ref<ECS::Scene>& context)
    {
        m_Context = context;
        m_SelectedEntity = {};
    }

    void SceneHierarchyPanel::OnImGuiRender()
    {
        ImGui::Begin("Scene Hierarchy");
        m_Context->m_Registry.each([&](auto entityID)
        {
            ECS::Entity entity{entityID, m_Context.get() };
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
        }
        ImGui::End();
    }
    void SceneHierarchyPanel::DrawEntityNode(ECS::Entity entity)
    {
        std::string& tag = entity.GetComponent<ECS::TagComponent>().Tag;

        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

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

    template<typename T, typename UIFunction>
    static void DrawComponent(const std::string& name, ECS::Entity entity, UIFunction uiFunction, bool removable=true)
    {
        if(entity.HasComponent<T>())
        {
            const ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding;
            auto& component = entity.GetComponent<T>();
            bool open = false;
            bool removeComponent = false;
            if(removable)
            {
                ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{4,4});
                float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
                ImGui::Separator();
                open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeFlags, name.c_str());
                ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
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
            } else {
                open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeFlags, name.c_str());
            }

            if(open)
            {
                uiFunction(component);
                ImGui::TreePop();
            }

            if(removeComponent && removable)
                entity.RemoveComponent<T>();
        }
    }

    void SceneHierarchyPanel::DrawComponents(ECS::Entity entity)
    {
        bool removeComponent = false;
        const ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_SpanAvailWidth;

        if(entity.HasComponent<ECS::TagComponent>())
        {
            std::string& tag = entity.GetComponent<ECS::TagComponent>().Tag;
            char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            strcpy(buffer, tag.c_str());
            if(ImGui::InputText("##Tag", buffer, sizeof(buffer)))
            {
                tag = std::string(buffer);
            }
        }

        ImGui::SameLine();
        ImGui::PushItemWidth(-1);

        if(ImGui::Button("Add Component"))
            ImGui::OpenPopup("AddComponent");
        
        if(ImGui::BeginPopup("AddComponent"))
        {
            if(ImGui::MenuItem("Camera"))
            {
                m_SelectedEntity.AddComponent<ECS::CameraComponent>();
                ImGui::CloseCurrentPopup();    
            }
            if(ImGui::MenuItem("Sprite Renderer"))
            {
                m_SelectedEntity.AddComponent<ECS::SpriteRendererComponent>();
                ImGui::CloseCurrentPopup();    
            }
            ImGui::EndPopup();
        }

        ImGui::PopItemWidth();

        DrawComponent<ECS::TransformComponent>("Transform", entity, [](auto& component)
        {
            DrawVec3Control("Position", component.Translation);
            glm::vec3 rotation = glm::degrees(component.Rotation);
            DrawVec3Control("Rotation", rotation);
            component.Rotation = glm::radians(rotation);
            DrawVec3Control("Scale", component.Scale, 1.0f);
        },false);

        DrawComponent<ECS::CameraComponent>("Camera", entity, [](auto& component)
        {		
            auto& camera = component.m_Camera;
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
	    	ImGui::Checkbox("Primary", &component.Primary);
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
        });

        DrawComponent<ECS::SpriteRendererComponent>("Sprite Renderer", entity, [](auto& component)
        {
                ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));
        });
    }
    static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue, float colWidth)
    {
        ImGuiIO& io = ImGui::GetIO();
        auto boldFont = io.Fonts->Fonts[0];

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
        ImGui::PushFont(boldFont);
        if(ImGui::Button("X", buttonSize))
            values.x = resetValue;
        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##X", &values.x, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.3f, 0.8f, 0.3f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
        ImGui::PushFont(boldFont);
        if(ImGui::Button("Y", buttonSize))
            values.y = resetValue;
        ImGui::PopFont();
        ImGui::PopStyleColor(3);
      
        ImGui::SameLine();
        ImGui::DragFloat("##Y", &values.y, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.2f, 0.25f, 0.8f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.2f, 0.35f, 0.9f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.2f, 0.25f, 0.8f, 1.0f});
        ImGui::PushFont(boldFont);
        if(ImGui::Button("Z", buttonSize))
            values.z = resetValue;
        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##Z", &values.z, 0.1f);
        ImGui::PopItemWidth();

        ImGui::PopStyleVar();

        ImGui::Columns(1);
                    
        ImGui::PopID();
    }

} // namespace VersaMachina