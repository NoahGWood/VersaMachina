#include <VM.h>
#include <ui/Panels/HardwarePanel.h>
#include <block/GraphEditor.h>

namespace VM
{
    // Graph Editor
    static GraphEditor::Options options;
    static GraphEditorDelegate delegate;
    static GraphEditor::ViewState viewState;
    static GraphEditor::FitOnScreen s_Fit = GraphEditor::Fit_None;
    
    HardwarePanel::HardwarePanel(std::shared_ptr<AppContext> ctx)
        : IPanel(std::move(ctx)){
            m_Name = "Hardware";
            delegate.m_AppContext = m_AppContext;
        }
    void HardwarePanel::Render(){
        if(ImGui::Begin(m_Name.c_str(), &m_IsOpen)){
            GraphEditor::EditOptions(options);
            if (ImGui::Button("Fit all nodes"))
            {
                s_Fit = GraphEditor::Fit_AllNodes;
            }
            ImGui::SameLine();
            if (ImGui::Button("Fit selected nodes"))
            {
                s_Fit = GraphEditor::Fit_SelectedNodes;
            }
            GraphEditor::Show(delegate, options, viewState, true, &s_Fit);
        }
        ImGui::End();
    }
} // namespace VM
