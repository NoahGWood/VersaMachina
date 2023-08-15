#include "panels/EditorSettingsPanel.h"

namespace VersaMachina
{
    void EditorSettingsPanel::OnImGuiRender()
    {
        ImGui::Begin("Settings");
            // Create Dropdowns
            if(ImGui::TreeNodeEx("EditorSettings"))
            {
                char buffer[255] = "test";
                if(ImGui::InputText("Test Settings sInput", buffer, sizeof(buffer)))
                {
                    VM_CORE_INFO("Entered: {0}", buffer);
                }
                ImGui::TreePop();
            }
        ImGui::End();
    }
} // namespace VersaMachina
