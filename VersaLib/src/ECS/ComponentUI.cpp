#include "pch.h"
#include "ECS/ComponentUI.h"

#include "imgui.h"
#include "imgui_internal.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <filesystem>

namespace VersaMachina
{
    namespace ECS
    {
        // Draw Entity Node
        void DrawEntityNode(Entity& entity, Scene& scene, Entity& selected)
        {
            std::string &tag = entity.GetComponent<TagComponent>().Tag;
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

            if (selected == entity)
                flags = ImGuiTreeNodeFlags_Selected | flags;
            bool opened = ImGui::TreeNodeEx((void *)(uint64_t)(uint32_t)entity, flags, tag.c_str());

            if (ImGui::IsItemClicked())
                selected = entity;
            bool deleted = false;
            if (ImGui::BeginPopupContextItem())
            {
                if (ImGui::MenuItem("Delete Entity"))
                    deleted = true;
                ImGui::EndPopup();
            }
            if (opened)
                ImGui::TreePop();
            if (deleted)
            {
                scene.DestroyEntity(entity);
                if (selected == entity)
                    selected = {};
            }
        }

        // Draw Component UI
        template <typename T, typename UIFunction>
        static void DrawComponentUI(const std::string &name, Entity& entity, UIFunction uiFunction, bool removable)
        {
            if (entity.HasComponent<T>())
            {
                const ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding;
                auto &component = entity.GetComponent<T>();
                bool open = false;
                bool removeComponent = false;
                if (removable)
                {
                    ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
                    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{4, 4});
                    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
                    ImGui::Separator();
                    open = ImGui::TreeNodeEx((void *)typeid(T).hash_code(), treeFlags, name.c_str());
                    ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
                    if (ImGui::Button("+", ImVec2{20, 20}))
                    {
                        ImGui::OpenPopup("ComponentSettings");
                    }
                    ImGui::PopStyleVar();
                    if (ImGui::BeginPopup("ComponentSettings"))
                    {
                        if (ImGui::MenuItem("Remove Component"))
                            removeComponent = true;
                        ImGui::EndPopup();
                    }
                }
                else
                {
                    open = ImGui::TreeNodeEx((void *)typeid(T).hash_code(), treeFlags, name.c_str());
                }

                if (open)
                {
                    uiFunction(component);
                    ImGui::TreePop();
                }

                if (removeComponent && removable)
                    entity.RemoveComponent<T>();
            }
        }
        template <>
        void DrawComponent<TagComponent>(Entity& e)
        {
            if (e.HasComponent<TagComponent>())
            {
                std::string &tag = e.GetComponent<TagComponent>().Tag;
                char buffer[256];
                memset(buffer, 0, sizeof(buffer));
                strncpy(buffer, tag.c_str(), sizeof(buffer));
                if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
                {
                    tag = std::string(buffer);
                }
            }
        }
        template <>
        void DrawComponent<TransformComponent>(Entity& e)
        {
            DrawComponentUI<TransformComponent>(
                "Transform", e, [](auto &component)
                {
                    DrawVec3Control("Position", component.Translation);
                    glm::vec3 rotation = glm::degrees(component.Rotation);
                    DrawVec3Control("Rotation", rotation);
                    component.Rotation = glm::radians(rotation);
                    DrawVec3Control("Scale", component.Scale, 1.0f); },
                false);
        }
        template <>
        void DrawComponent<SpriteRendererComponent>(Entity& e)
        {
            DrawComponentUI<ECS::SpriteRendererComponent>
            ("Sprite Renderer", e, [](auto &component)
            {
                ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));
                
                ImGui::Button("Texture", ImVec2{100.0f, 0.0f});

                if (ImGui::BeginDragDropTarget())
        		{
        			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
        			{
                        // IDK why but you need to pass char*, even though this IS supposed to be wchar_t*
                        std::filesystem::path path = (char*)payload->Data;
                        auto ext = path.extension();
                        if(ext == ".png")
                            component.Texture = Render::Texture2D::Create(path.string());
        			}
        			ImGui::EndDragDropTarget();
        		}
                ImGui::DragFloat("Tiling Factor", &component.TilingFactor, 0.1f, 0.0f, 100.0f);
            });
        }
        template <>
        void DrawComponent<CameraComponent>(Entity& e)
        {
            DrawComponentUI<ECS::CameraComponent>("Camera", e, [](auto &component)
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
                camera->SetRotateSpeed(rotateSpeed); });
        }
        template <>
        void DrawComponent<NativeScriptComponent>(Entity& e)
        {
        }
        template <>
        void DrawComponent<ScriptComponent>(Entity& e)
        {
        }

        // Draw Component Settings

        // Draw AddComponent Popup

        // Vec3 Controls
        void DrawVec3Control(const std::string &label, glm::vec3 &values, float resetValue, float colWidth)
        {
            ImGuiIO &io = ImGui::GetIO();
            auto boldFont = io.Fonts->Fonts[0];

            ImGui::PushID(label.c_str());

            ImGui::Columns(2);
            ImGui::SetColumnWidth(0, colWidth);
            ImGui::Text(label.c_str());
            ImGui::NextColumn();

            ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

            float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
            ImVec2 buttonSize = {lineHeight + 3.0f, lineHeight};

            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.9f, 0.2f, 0.2f, 1.0f});
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
            ImGui::PushFont(boldFont);
            if (ImGui::Button("X", buttonSize))
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
            if (ImGui::Button("Y", buttonSize))
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
            if (ImGui::Button("Z", buttonSize))
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

    } // namespace ECS

} // namespace VersaMachina
