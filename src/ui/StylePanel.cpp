#include <VM.h>
#include <ui/Panels/StylePanel.h>

namespace VM
{

    void StylePanel::Render(){
        if(ImGui::Begin(m_Name.c_str(), &m_IsOpen)){
            ImGui::ShowStyleEditor();
        }
        ImGui::End();
    }
} // namespace VM
