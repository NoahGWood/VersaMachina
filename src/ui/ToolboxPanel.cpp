#include <VM.h>
#include <ui/Panels/ToolboxPanel.h>

namespace VM
{

    void ToolboxPanel::Render(){
        if(ImGui::Begin(m_Name.c_str(), &m_IsOpen)){

        }
        ImGui::End();
    }
} // namespace VM
