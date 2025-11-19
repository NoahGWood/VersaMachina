#include <VM.h>
#include <ui/Panels/ProjectPanel.h>

namespace VM
{
    using LifecycleCallback = std::function<void(VM::Project &, entt::entity)>;
    static entt::entity s_ToDelete = entt::null;
    static entt::entity s_ToRename = entt::null;

    void ProjectPanel::RenderEntityNode(entt::entity e)
    {
        auto &registry = m_AppContext->project().GetRegistry();
        auto tag = m_AppContext->project().GetComponent<TagComponent>(e);
        auto h = m_AppContext->project().GetComponent<HierarchyComponent>(e);

        if (s_ToRename == e)
        {
            if(ImGui::IsKeyPressed(ImGuiKey_Escape)) s_ToRename = entt::null;
            
            DrawStringField(m_AppContext, e, "Name", tag.name,
                [s_ToRename](Project &proj, entt::entity ent) -> std::string &
                { s_ToRename = entt::null; return proj.GetComponent<TagComponent>(ent).name; });
        }
        else
        {

            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

            if (m_AppContext->project().GetSelected() == e)
                flags |= ImGuiTreeNodeFlags_Selected;
            if (h.children.empty())
                flags |= ImGuiTreeNodeFlags_Leaf;

            ImGui::PushID((int)entt::to_integral(e));
            bool opened = ImGui::TreeNodeEx("EntityNode", flags, "%s", tag.name.c_str());
            ImGui::PopID();

            if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
                m_AppContext->project().SelectEntity(e);

            // Drag source (this entity)
            entt::entity payloadEntity = e;
            if (ImGui::BeginDragDropSource())
            {
                ImGui::SetDragDropPayload("DND_ENTITY", &payloadEntity, sizeof(entt::entity));
                ImGui::Text("Move \"%s\"", tag.name.c_str());
                ImGui::EndDragDropSource();
            }
            // Drop target (make node new parent / reorder)
            if (ImGui::BeginDragDropTarget())
            {
                if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("DND_ENTITY"))
                {
                    auto dropped = *static_cast<const entt::entity *>(payload->Data);
                    if (dropped != e)
                    {
                        m_AppContext->cmdManager().Run(
                            std::make_unique<ReparentEntityCommand>(dropped, e),
                            m_AppContext->project());
                        // m_AppContext->project().ReparentAndReorder(dropped, e);
                    }
                }
                ImGui::EndDragDropTarget();
            }
            if (ImGui::BeginPopupContextItem())
            {
                if (ImGui::MenuItem("Rename"))
                {
                    s_ToRename = e;
                }
                if (ImGui::MenuItem("New Child"))
                {
                    entt::entity parent = e;
                    auto createCb = [parent](Project &proj, entt::entity child)
                    {
                        CORE_INFO("Creating new child!");
                        proj.SetParent(child, parent);
                    };

                    m_AppContext->cmdManager().Run(
                        std::make_unique<CreateEntityCommand>("New Entity", createCb),
                        m_AppContext->project());
                }
                if (ImGui::MenuItem("Delete Entity"))
                {
                    s_ToDelete = e;
                }
                ImGui::EndPopup();
            }
            if (opened)
            {
                for (auto child : h.children)
                    RenderEntityNode(child);
                ImGui::TreePop();
            }
        }
    }

    void ProjectPanel::Render()
    {
        if (ImGui::Begin(m_Name.c_str(), &m_IsOpen))
        {
            if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !ImGui::IsAnyItemActive())
            {
                m_AppContext->project().DeselectEntity();
            }

            auto &project = m_AppContext->project();
            auto &registry = project.GetRegistry();

            auto view = registry.view<TagComponent, HierarchyComponent>();
            for (auto [e, tag, h] : view.each())
            {
                if (h.parent == entt::null)
                    RenderEntityNode(e);
            }

            if (ImGui::BeginPopupContextWindow("RightClickContextMenu", ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems))
            {
                if (ImGui::BeginMenu("New"))
                {
                    if (ImGui::MenuItem("Entity"))
                    {
                        // m_AppContext->project().CreateEntity("New Entity");
                        m_AppContext->cmdManager().Run(
                            std::make_unique<CreateEntityCommand>("New Entity"),
                            m_AppContext->project());
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndPopup();
            }

            // Drop target (unparent node)
            ImGui::Dummy(ImGui::GetContentRegionAvail());
            if (ImGui::BeginDragDropTarget())
            {
                if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("DND_ENTITY"))
                {
                    auto dropped = *static_cast<const entt::entity *>(payload->Data);
                    if (dropped != entt::null)
                    {
                        m_AppContext->cmdManager().Run(
                            std::make_unique<ReparentEntityCommand>(dropped, entt::null),
                            m_AppContext->project());
                        // m_AppContext->project().SetParent(dropped, entt::null);
                    }
                }
                ImGui::EndDragDropTarget();
            }
        }
        ImGui::End();
        if (s_ToDelete != entt::null)
        {
            // m_AppContext->project().DestroyEntity();
            m_AppContext->cmdManager().Run(std::make_unique<DeleteEntityCommand>(s_ToDelete), m_AppContext->project());
            s_ToDelete = entt::null;
        }
    }
} // namespace VM
