#pragma once
#include "common/Base.h"
#include "ecs/Components.h"
#include "app/AppContext.h"
#include "cmd/EditFieldCommand.h"

namespace VM
{
    template<typename T, typename F>
    static void DrawComponentTitleBar(std::shared_ptr<AppContext> ctx, entt::entity e, const std::string& label, F&& drawBody)
    {
        ImGui::PushID(label.c_str());
        ImGui::Columns(2, nullptr, false);

        ImGuiTreeNodeFlags flags =
            ImGuiTreeNodeFlags_OpenOnArrow |
            ImGuiTreeNodeFlags_SpanAvailWidth;

        bool open = ImGui::TreeNodeEx("##node", flags);

        ImGui::SameLine();
        ImGui::TextUnformatted(label.c_str());
        
        ImGui::NextColumn();
        ImGui::SetColumnWidth(-1, ImGui::GetFrameHeight() * 2.0f);
        if (ImGui::SmallButton("x")){
            // TODO: Implement command system fx
            ctx->project().RemoveComponent<T>(e);
        }
        ImGui::Columns(1);
        if (open)
        {
            drawBody();
            ImGui::TreePop();
        }
        ImGui::PopID();
    }
    static void DrawFloatField(std::shared_ptr<AppContext> ctx, entt::entity e,
        const std::string& label, float value, EditFieldCommand<float>::Accessor accessor)
    {
        float oldValue = value;
        ImGui::DragFloat(label.c_str(), &value, 0.1f);
        if(ImGui::IsItemDeactivatedAfterEdit() && oldValue != value){
            ctx->cmdManager().Run(std::make_unique<EditFieldCommand<float>>(e, accessor, oldValue, value), ctx->project());
        }
    }

    // vec2
    static void DrawVec2Field(const std::shared_ptr<AppContext>& ctx,
                              entt::entity e,
                              const std::string& label,
                              glm::vec2& value,
                              EditFieldCommand<glm::vec2>::Accessor accessor,
                              float min = -100.0f, float max = 100.0f)
    {
        glm::vec2 oldValue = value;
        float v[2] = { value.x, value.y };

        ImGui::DragFloat2(label.c_str(), v, 0.1f, min, max, "%.1f");
        value = { v[0], v[1] };

        if (ImGui::IsItemDeactivatedAfterEdit() && value != oldValue) {
            ctx->cmdManager().Run(
                std::make_unique<EditFieldCommand<glm::vec2>>(e, accessor, oldValue, value),
                ctx->project()
            );
        }
    }

    // vec3
    static void DrawVec3Field(const std::shared_ptr<AppContext>& ctx,
                              entt::entity e,
                              const std::string& label,
                              glm::vec3& value,
                              EditFieldCommand<glm::vec3>::Accessor accessor,
                              float min = -100.0f, float max = 100.0f)
    {
        glm::vec3 oldValue = value;
        float v[3] = { value.x, value.y, value.z };

        ImGui::DragFloat3(label.c_str(), v, 0.1f, min, max, "%.1f");
        value = { v[0], v[1], v[2] };

        if (ImGui::IsItemDeactivatedAfterEdit() && value != oldValue) {
            ctx->cmdManager().Run(
                std::make_unique<EditFieldCommand<glm::vec3>>(e, accessor, oldValue, value),
                ctx->project()
            );
        }
    }

    // string
    static void DrawStringField(const std::shared_ptr<AppContext>& ctx,
                                entt::entity e,
                                const std::string& label,
                                std::string& value,
                                EditFieldCommand<std::string>::Accessor accessor)
    {
        std::string oldValue = value;

        char buf[256];
        std::strncpy(buf, value.c_str(), sizeof(buf));
        buf[sizeof(buf)-1] = '\0';

        if(ImGui::InputText(label.c_str(), buf, sizeof(buf), ImGuiInputTextFlags_EnterReturnsTrue)){
            value = buf;
            if(value != oldValue){
                ctx->cmdManager().Run(
                    std::make_unique<EditFieldCommand<std::string>>(e, accessor, oldValue, value),
                    ctx->project()
                );               
            }
        }
    }

    // Unity-style list of strings (no reordering yet, just add/remove + inline edit)
    static void DrawListStringField(const std::shared_ptr<AppContext>& ctx,
                                    entt::entity e,
                                    const std::string& label,
                                    std::vector<std::string>& values,
                                    EditFieldCommand<std::vector<std::string>>::Accessor accessor)
    {
        const auto oldValues = values;   // snapshot for undo
        bool changed = false;
        auto flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

        if(ImGui::TreeNodeEx(label.c_str(), flags))
        {
            ImGui::BeginChild((label + "##list").c_str(), ImVec2(0, 150), true);
            for (int i = 0; i < (int)values.size(); )
            {
                bool erased = false;
                ImGui::PushID(i);

                ImGui::SetNextItemWidth(-ImGui::GetFrameHeight() * 2.0f);

                // Inline edit of element; mark changed if text changed
                if (ImGui::InputText("##value", &values[i]))
                    changed = true;

                ImGui::SameLine();
                if (ImGui::Button("-"))
                {
                    values.erase(values.begin() + i);
                    erased = true;
                    changed = true;
                }

                ImGui::PopID();
                if (!erased) ++i;
            }

            ImGui::EndChild();

            if (ImGui::Button(("Add " + label + "##add").c_str()))
            {
                values.emplace_back("");
                changed = true;
            }

            ImGui::TreePop();
        }



        // Only push command if something actually changed
        if (changed && values != oldValues)
        {
            ctx->cmdManager().Run(
                std::make_unique<EditFieldCommand<std::vector<std::string>>>(
                e, accessor, oldValues, values),
                ctx->project()
            );
        }
    }

    template<typename T>
    static void DrawComponentDelete(const std::shared_ptr<AppContext> ctx, entt::entity e){
        ImGui::SameLine();
        if(ImGui::Button("-")){
            // TODO: Implement command system fx
            ctx->project().RemoveComponent<T>(e);
        }
    }


} // namespace VM
