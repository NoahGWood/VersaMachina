#include <VM.h>
#include <ui/MainPanel.h>

namespace VM
{

    void MainPanel::Render(){
        if(ImGui::Begin(m_Name.c_str(), &m_IsOpen)){

        }
        ImGui::End();
    }
} // namespace VM
