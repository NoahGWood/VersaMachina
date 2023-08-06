#include "EditorLayer.h"
#include "Console.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace VersaMachina
{
    EditorLayer::EditorLayer()
    : Layer("EditorLayer"), m_CameraController() { }

    void EditorLayer::OnAttach()
    {
    	m_CheckerboardTexture = Render::Texture2D::Create("VersaEditor/assets/textures/versa_logo_blank.png");
        
        Render::FramebufferSpecification fbSpec;
        fbSpec.Width = 1280;
        fbSpec.Height = 720;
        m_Framebuffer = Render::Framebuffer::Create(fbSpec);

        // Create scene and add objects

        m_Scene = CreateRef<Scenes::Scene>();
        m_Camera = new Camera::Camera();

        m_SquareEntity = m_Scene->CreateEntity("Square");
        m_SquareEntity.AddComponent<Scenes::SpriteRendererComponent>(glm::vec4{0.5f, 0.5f, 0.5f, 1.0f});
        m_SquareEntity.GetComponent<Scenes::SpriteRendererComponent>().Texture = m_CheckerboardTexture;

        m_CameraEntity = m_Scene->CreateEntity("Camera Entity");
        m_CameraEntity.AddComponent<Scenes::CameraComponent>();

        class CameraController : public Scenes::ScriptableEntity
        {
            public:
                void OnCreate()
                {
                    //GetComponent<Scenes::TransformComponent>();
                }

                void OnDestroy()
                {

                }

                void OnUpdate(Timestep ts)
                {
                    auto& transform = GetComponent<Scenes::TransformComponent>().Transform;

    				float speed = 0.005f;

    				if (Input::Input::IsKeyPressed(Key::A))
    					transform[3][0] -= speed * ts;
    				if (Input::Input::IsKeyPressed(Key::D))
    					transform[3][0] += speed * ts;
    				if (Input::Input::IsKeyPressed(Key::W))
    					transform[3][1] += speed * ts;
    				if (Input::Input::IsKeyPressed(Key::S))
    					transform[3][1] -= speed * ts;
                }
        };
        m_CameraEntity.AddComponent<Scenes::NativeScriptComponent>().Bind<CameraController>();

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

        // Update camera
        if(m_ViewportFocused)
            m_CameraController.OnUpdate(ts);

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
        m_CameraController.OnEvent(e);
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
                ImGui::MenuItem("New");
                ImGui::MenuItem("Open");
                ImGui::MenuItem("Save");
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
            Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

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

} // namespace VersaMachina

