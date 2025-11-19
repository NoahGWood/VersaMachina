#include <VM.h>
#include <ui/Panels/InspectorPanel.h>

namespace VM
{

    static char s_NameBuf[256];

    void InspectorPanel::Render(){
        if(ImGui::Begin(m_Name.c_str(), &m_IsOpen)){
            auto& proj = m_AppContext->project();
            auto selected = proj.GetSelected();

            if(selected != entt::null){
                auto& tag = proj.GetComponent<TagComponent>(selected);
                DrawStringField(m_AppContext, selected, "Name", tag.name,
                    [](Project& p, entt::entity ent) -> std::string& {
                    return p.GetComponent<TagComponent>(ent).name;
                });
                if(proj.HasComponent<BlockInstance>(selected)){
                    DrawComponentTitleBar<BlockInstance>(m_AppContext, selected, "Electrical Block", [this, &proj, selected]{
                        auto& block = proj.GetComponent<BlockInstance>(selected);
                        ImGui::InputText("Prefab", &block.blockId, ImGuiInputTextFlags_ReadOnly);
                        DrawStringField(this->m_AppContext, selected, "Label", block.label, [](Project& p, entt::entity e) -> std::string& {
                            return p.GetComponent<BlockInstance>(e).label;
                        });
                        DrawListStringField(this->m_AppContext, selected, "Ports", block.ports, [](Project& p, entt::entity e) -> std::vector<std::string>& {
                            return p.GetComponent<BlockInstance>(e).ports;
                        });
                    });
                }
                if(ImGui::Button("AddComponent")){
                    ImGui::OpenPopup("AddComponent");
                }

                if(ImGui::BeginPopup("AddComponent")){
                    if(!proj.HasComponent<BlockInstance>(selected)){
                        if(ImGui::Button("Electrical Block")){
                            proj.AddComponent<BlockInstance>(selected);
                        }
                    }

                    ImGui::EndPopup();
                }
            }
        }
        ImGui::End();
    }
} // namespace VM
