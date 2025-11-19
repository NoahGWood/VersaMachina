#pragma once
#include <ui/IMenu.h>
#include <ecs/ProjectSerializer.h>

namespace VM
{
    class FileMenu : public IMenu
    {
        public:
            FileMenu(std::shared_ptr<AppContext> context)
                : IMenu(std::move(context)) { m_Name = "File"; }
            ~FileMenu(){ }
            void Open() { m_IsOpen = true; }
            void Tick() override {}
            void Render() override {
                if(ImGui::BeginMenu(m_Name.c_str())){
                    if(ImGui::BeginMenu("New")){
                        ImGui::MenuItem("Project");
                        ImGui::MenuItem("ECU");
                        ImGui::EndMenu();
                    }
                    if(ImGui::BeginMenu("Open")){
                        if(ImGui::MenuItem("Open Project", "Ctrl+O")){
                            OpenProject();
                        }
                        ImGui::Separator();
                        if(ImGui::MenuItem("Project 1")){

                        }
                        if(ImGui::MenuItem("Project 2")){

                        }
                        ImGui::EndMenu();
                    }
                    if(ImGui::BeginMenu("Save")){
                        if(ImGui::MenuItem("Save", "Ctrl+S")){
                            if(m_AppContext->project().GetName() == "New Project"){
                                SaveAs();
                            } else {
                                Save();
                            }
                        }
                        if(ImGui::MenuItem("Save As...")){
                            SaveAs();
                        }
                        ImGui::EndMenu();
                    }


                    ImGui::EndMenu();
                }
            }
        private:
            void Save(){
                m_AppContext->project().Save();
            }
            void SaveAs(){
                char const *lFilterPatterns[2] = {"*.vproj", "*.yaml"};
                char *out = tinyfd_saveFileDialog("Save Project", m_AppContext->project().GetName().c_str(), 2, lFilterPatterns, "VProj File");
                if (out)
                {
                    m_AppContext->project().SaveAs(out);
                }
            }
            void OpenProject(){
                char const* lFilterPatterns[2] = {"*.vproj", "*.yaml"};
                char *out = tinyfd_openFileDialog("Open Project", "", 2, lFilterPatterns, "Project Files", 0);
                if(out){
                    ProjectSerializer ser(m_AppContext->project());
                    ser.Deserialize(out);
                }
            }
    };
} // namespace VM
