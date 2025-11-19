#include <VM.h>
#include <ui/Panels/ConsolePanel.h>

namespace VM
{

    static bool s_AutoScroll = true;
    static ImGuiTextFilter s_Filter;
    static char s_InputBuf[256];
    static bool _pop = false;
    void ConsolePanel::Render(){
        if(ImGui::Begin(m_Name.c_str(), &m_IsOpen)){

            auto sink = VM::Logger::GetImGuiSink();
            if(ImGui::Button("Clear") && sink) sink->Clear();
            ImGui::SameLine();
            if(ImGui::Button("Critical")) CORE_CRITICAL("CRITICAL!");
            ImGui::SameLine();
            if(ImGui::Button("Error")) CORE_ERROR("ERROR!");
            ImGui::SameLine();
            if(ImGui::Button("Warn")) CORE_WARN("WARNING!");
            ImGui::SameLine();
            if(ImGui::Button("INFO")) CORE_INFO("INFO!");
            ImGui::SameLine();
            if(ImGui::Button("TRACE")) CORE_TRACE("TRACE!");
            

            ImGui::Checkbox("Auto-Scroll", & s_AutoScroll);

            s_Filter.Draw("Filter");
            ImGui::Separator();
            if(ImGui::BeginChild("##consoleChildWindow")){
                if (sink) {
                    for (auto& e : sink->Entries()) {
                        if(!s_Filter.PassFilter(e.message.c_str())) continue;

                        switch(e.level){
                            case spdlog::level::trace:{
                                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(211,211,211,127));
                                _pop=true;
                                break;
                            }
                            case spdlog::level::info: {
                                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0,255,255,255));
                                _pop=true;
                                break;
                            }
                            case spdlog::level::warn: {
                                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 200, 0, 255));
                                _pop=true;
                                break;
                            }
                            case spdlog::level::err: {
                                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 80, 80, 255));
                                _pop=true;
                                break;
                            }
                            case spdlog::level::critical: {
                                ImVec2 pos = ImGui::GetCursorScreenPos();
                                ImVec2 textSize = ImGui::CalcTextSize(e.message.c_str());
                                ImGui::GetWindowDrawList()->AddRectFilled(
                                    pos,
                                    ImVec2(pos.x + textSize.x, pos.y + textSize.y),
                                    IM_COL32(255,0,0,255)
                                );
                                _pop = false;
                                break;
                            }
                            default:
                                _pop = false;
                                break;
                        }

                        ImGui::TextUnformatted(e.message.c_str());
                        if (_pop)
                            ImGui::PopStyleColor();
                    }
                }
                if(s_AutoScroll)
                    ImGui::SetScrollHereY(1.0f);
                ImGui::EndChild();
            }

            if(ImGui::InputText("##consoleInput", s_InputBuf, sizeof(s_InputBuf), ImGuiInputTextFlags_EnterReturnsTrue)){
                CORE_INFO("Command: {}", s_InputBuf);
                // m_AppContext->cmdManager(). // ToDo: Named commands for running
                s_InputBuf[0] = '\0';
            }
        }
        ImGui::End();
    }
} // namespace VM
