#include "pch.h"
#include "UI/ImGUILayer.h"
#include "Core/Application.h"
#include "imgui.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <ImGuizmo.h>

// TEMPORARY
#include <GLFW/glfw3.h>


namespace VersaMachina
{
    namespace UI
    {
        ImGUILayer::ImGUILayer()
            : Layer("ImGUI")
        {
            VM_PROFILE_FUNCTION();
        }

        ImGUILayer::~ImGUILayer()
        {
            VM_PROFILE_FUNCTION();
        }

        void ImGUILayer::OnAttach()
        {
            VM_PROFILE_FUNCTION();

            // Setup Dear ImGui context
		    IMGUI_CHECKVERSION();
		    ImGui::CreateContext();
		    ImGuiIO& io = ImGui::GetIO(); (void)io;
		    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
            io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;
            io.BackendFlags |= ImGuiBackendFlags_RendererHasViewports; 
		    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;
            io.Fonts->AddFontFromFileTTF("VersaEditor/assets/fonts/OpenSans/static/OpenSans-Bold.ttf", 18.0f);
            io.FontDefault = io.Fonts->AddFontFromFileTTF("VersaEditor/assets/fonts/OpenSans/static/OpenSans-Regular.ttf", 18.0f);

    		// Setup Dear ImGui style
    		ImGui::StyleColorsDark();
    		//ImGui::StyleColorsClassic();


            // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    		ImGuiStyle& style = ImGui::GetStyle();
    		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    		{
    			style.WindowRounding = 0.0f;
    			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    		}

    		Application& app = Application::Get();
    		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

    		// Setup Platform/Renderer bindings
    		ImGui_ImplGlfw_InitForOpenGL(window, true);
    		ImGui_ImplOpenGL3_Init("#version 410");
        }
        void ImGUILayer::OnDetach()
        {
            VM_PROFILE_FUNCTION();

    		ImGui_ImplOpenGL3_Shutdown();
    		ImGui_ImplGlfw_Shutdown();
    		ImGui::DestroyContext();
        }


        void ImGUILayer::Begin()
        {
            VM_PROFILE_FUNCTION();

            ImGui_ImplOpenGL3_NewFrame();
    		ImGui_ImplGlfw_NewFrame();
    		ImGui::NewFrame();
            ImGuizmo::BeginFrame();
        }

        void ImGUILayer::End()
        {
            VM_PROFILE_FUNCTION();

            ImGuiIO& io = ImGui::GetIO();
            Application& app = Application::Get();
    		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
            // Rendering
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                GLFWwindow* backup_current_context = glfwGetCurrentContext();
    			ImGui::UpdatePlatformWindows();
    			ImGui::RenderPlatformWindowsDefault();
    			glfwMakeContextCurrent(backup_current_context);
            }
        }

        void ImGUILayer::OnImGuiRender()
        {
        }


        void ImGUILayer::OnEvent(Event& e)
        {
            if(m_BlockEvents)
            {
                ImGuiIO& io = ImGui::GetIO();
    			e.m_Handled |= e.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
    			e.m_Handled |= e.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
            }
        }
    } // namespace UI

} // namespace VersaMachina
