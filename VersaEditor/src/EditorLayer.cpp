#include "EditorLayer.h"
#include "Console.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ECS/SceneSerializer.h"

#include <tinyfiledialogs/tinyfiledialogs.h>

namespace VersaMachina
{
    EditorLayer::EditorLayer()
    : Layer("EditorLayer") { }

    void EditorLayer::OnAttach()
    {
//    	m_CheckerboardTexture = Render::Texture2D::Create("VersaEditor/assets/textures/versa_logo_blank.png");
        
        Render::FramebufferSpecification fbSpec;
        fbSpec.Width = 1280;
        fbSpec.Height = 720;
        m_Framebuffer = Render::Framebuffer::Create(fbSpec);

        // Create scene and add objects

        m_Scene = CreateRef<ECS::Scene>();

        // m_CameraEntity = m_Scene->CreateEntity("Camera Entity");
        // m_CameraEntity.AddComponent<ECS::CameraComponent>();

        // class CameraController : public ECS::ScriptableEntity
        // {
        //     public:
        //         void OnCreate()
        //         {
        //             //GetComponent<ECS::TransformComponent>();
        //         }

        //         void OnDestroy()
        //         {

        //         }

        //         void OnUpdate(Timestep ts)
        //         {
        //             auto& transform = GetComponent<ECS::TransformComponent>();
        //             if(HasComponent<ECS::CameraComponent>()){
        //                 auto& camera = GetComponent<ECS::CameraComponent>().m_Camera;

        // 				float speed = 0.005f;

        // 				if (Input::Input::IsKeyPressed(Key::A))
        // 					transform.Translation.x -= speed * ts;
        // 				if (Input::Input::IsKeyPressed(Key::D))
        // 					transform.Translation.x += speed * ts;
        // 				if (Input::Input::IsKeyPressed(Key::W))
        // 					transform.Translation.y += speed * ts;
        // 				if (Input::Input::IsKeyPressed(Key::S))
        // 					transform.Translation.y -= speed * ts;

        //                 camera->SetTransform(transform.GetTransform());
        //             }
        //         }
        // };
        // m_CameraEntity.AddComponent<ECS::NativeScriptComponent>().Bind<CameraController>();

        // m_SquareEntity = m_Scene->CreateEntity("Square");
        // m_SquareEntity.AddComponent<ECS::SpriteRendererComponent>(glm::vec4{0.5f, 0.5f, 0.5f, 1.0f});
        // m_SquareEntity.GetComponent<ECS::SpriteRendererComponent>().Texture = m_CheckerboardTexture;

        m_SceneHierarchyPanel.SetContext(m_Scene);

    }
    void EditorLayer::OnDetach()
    {
    }
    void EditorLayer::OnUpdate(Timestep ts)
    {
        VM_PROFILE_FUNCTION();
        Render::FramebufferSpecification spec = m_Framebuffer->GetSpecification();
    	if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
    		(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
    	{
    		m_Framebuffer->Resize(m_ViewportSize.x, m_ViewportSize.y);
    		m_Scene->OnViewportResize(m_ViewportSize.x, m_ViewportSize.y);
    	}

//    // Update camera
//    if(m_ViewportFocused)
//
        Render::Renderer2D::ResetStats();
        m_Framebuffer->Bind();
        Render::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        Render::RenderCommand::Clear();
    
        // Update scene
        m_Scene->OnUpdate(ts);    
        m_Framebuffer->Unbind();
    }

    void EditorLayer::OnEvent(Event &e)
    {
        VersaMachina::EventDispatcher dispatcher(e);

        dispatcher.Dispatch<KeyPressedEvent>(VM_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
    }


    void EditorLayer::OnImGuiRender()
    {
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        // Create Scene Hierachy
        m_SceneHierarchyPanel.OnImGuiRender();

        // Create console 
        ShowConsole();

        if(ImGui::BeginMainMenuBar())
        {
            if(ImGui::BeginMenu("File"))
            {
                if(ImGui::MenuItem("New", "Ctrl+N"))
                {
                    NewScene();
                }
                if(ImGui::MenuItem("Open", "Ctrl+O"))
                {
                    Open();
                }
                if(ImGui::MenuItem("Save",  "Ctrl+S"))
                {
                    Save();
                }
                if(ImGui::MenuItem("Save As",  "Ctrl+Shift+S"))
                {
                    SaveAs();
                }
                ImGui::EndMenu();
            }
            if(ImGui::BeginMenu("Edit"))
            {
                ImGui::EndMenu();
            }
            if(ImGui::BeginMenu("View"))
            {
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        ImGui::ShowDemoWindow();

        ImGui::Begin("Project Hierarchy");

        if(ImGui::CollapsingHeader("Modules"))
        {
            ImGui::CollapsingHeader("Air Conditioning Compressor Control Module");
            ImGui::CollapsingHeader("Airbag Control Module");
            ImGui::CollapsingHeader("Anti-Lock Braking System Module");
            ImGui::CollapsingHeader("Audio Amplifier Control Module");
            ImGui::CollapsingHeader("Battery Charging Control Module");
            ImGui::CollapsingHeader("Battery Management Module");
            ImGui::CollapsingHeader("Battery Monitoring Control Module");
            ImGui::CollapsingHeader("Body Control Module");
            ImGui::CollapsingHeader("Cruise Control Module");
            ImGui::CollapsingHeader("Door Control Module");
            ImGui::CollapsingHeader("Electric Motor Control Module");
            ImGui::CollapsingHeader("Electric Power Steering Control Module");
            ImGui::CollapsingHeader("Electronic Stability Program (ESP) Control Module");
            ImGui::CollapsingHeader("Engine Control Module");
            ImGui::CollapsingHeader("Exhaust Gas Recirculation (EGR) Control Module");
            ImGui::CollapsingHeader("Fuel Injection Control Module");
            ImGui::CollapsingHeader("Fuel Pump Control Module");
            ImGui::CollapsingHeader("Gauge Control Module");
            ImGui::CollapsingHeader("HVAC Control Module");
            ImGui::CollapsingHeader("HVAC Zone Control Module");
            ImGui::CollapsingHeader("Ignition Control Module");
            ImGui::CollapsingHeader("Infotainment Module");
            ImGui::CollapsingHeader("Keyless Entry Control Module");
            ImGui::CollapsingHeader("LiDAR Control Module");
            ImGui::CollapsingHeader("Lighting Control Module");
            ImGui::CollapsingHeader("Parking Assist Control Module");
            ImGui::CollapsingHeader("Power Window Control Module");
            ImGui::CollapsingHeader("Powertrain Control Module");
            ImGui::CollapsingHeader("Radar Control Module");
            ImGui::CollapsingHeader("Steering Control Module");
            ImGui::CollapsingHeader("Suspension Control Module");
            ImGui::CollapsingHeader("Throttle Control Module");
            ImGui::CollapsingHeader("Tire Pressure Monitoring System");
            ImGui::CollapsingHeader("Transmission Control Module");
            ImGui::CollapsingHeader("Vehicle Stability Control Module");
            ImGui::CollapsingHeader("Wiper Control Module");
        }

        ImGui::End();

        // Viewport
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0,0});
    	ImGui::Begin("Viewport");
            m_ViewportFocused = ImGui::IsWindowFocused();
            m_ViewportHovered = ImGui::IsWindowHovered();
//            Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

            ImVec2 viewportSize = ImGui::GetContentRegionAvail();
            m_ViewportSize = { viewportSize.x, viewportSize.y };

            uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();

            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Wint-to-pointer-cast" // Ignore warning caused by pointer conversion of int
                ImGui::Image((void*)textureID, viewportSize, ImVec2{0,1}, ImVec2{1,0});
            #pragma GCC diagnostic pop      
        ImGui::End();
        ImGui::PopStyleVar();

        // Simulator
        ImGui::Begin("Simulator");
        ImGui::End();
        // Inspector
        ImGui::Begin("Project");
        ImGui::End();
    }

    bool EditorLayer::OnKeyPressed(VersaMachina::KeyPressedEvent& e)
    {
        if(e.IsRepeat())
            return false;
        bool control = VersaMachina::Input::IsKeyPressed(Key::LeftControl) || VersaMachina::Input::IsKeyPressed(Key::RightControl);
        bool shift = VersaMachina::Input::IsKeyPressed(Key::LeftShift) || VersaMachina::Input::IsKeyPressed(Key::RightShift);

        switch(e.GetKeyCode())
        {
            case Key::N:
            {
                if(control)
                    NewScene();
                break;
            }
            case Key::O:
            {
                if(control)
                    Open();
                break;
            }
            case Key::S:
            {
                if(control)
                {
                    if(shift)
                    {
                        SaveAs();
                    } else {
                        Save();
                    }
                }
                break;
            }
        }

    }

    void EditorLayer::NewScene()
    {
        m_Scene = CreateRef<ECS::Scene>();
        m_Scene->OnViewportResize(m_ViewportSize.x, m_ViewportSize.y);
        m_SceneHierarchyPanel.SetContext(m_Scene);
        m_SceneFile = "NewProject.versa";
    }
    void EditorLayer::Open()
    {
        char const * lFilterPatterns[2] = {"*.versa", "*.yaml"};
        char* out = tinyfd_openFileDialog("Open Project", "", 2, lFilterPatterns, "Project Files", 0);
        if(out){
            m_Scene = CreateRef<ECS::Scene>();
            m_Scene->OnViewportResize(m_ViewportSize.x, m_ViewportSize.y);
            m_SceneHierarchyPanel.SetContext(m_Scene);
            ECS::SceneSerializer serializer(m_Scene);
            serializer.Deserialize(out);
        }
    }
    void EditorLayer::Save()
    {
        ECS::SceneSerializer serializer(m_Scene);
        serializer.Serialize(m_SceneFile);
    }
    void EditorLayer::SaveAs()
    {
        char const * lFilterPatterns[2] = {"*.versa", "*.yaml"};
        char* out = tinyfd_saveFileDialog("Save Project", m_SceneFile.c_str(), 2, lFilterPatterns, "Save Project");
        if(out)
        {
            ECS::SceneSerializer serializer(m_Scene);
            serializer.Serialize(out);
            m_SceneFile = (std::string)out;
        }
    }
} // namespace VersaMachina

