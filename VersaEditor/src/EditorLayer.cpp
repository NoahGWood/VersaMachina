#include "EditorLayer.h"
#include "Console.h"
#include "ECS/SceneSerializer.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <tinyfiledialogs/tinyfiledialogs.h>

namespace VersaMachina
{
    EditorLayer::EditorLayer()
    : Layer("EditorLayer") { }

    void EditorLayer::OnAttach()
    {
//    	m_CheckerboardTexture = Render::Texture2D::Create("VersaEditor/assets/textures/versa_logo_blank.png");
        m_EditorCamera = Camera::EditorCamera();
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
            m_EditorCamera.Resize(m_ViewportSize.x, m_ViewportSize.y);
    	}
        if(m_ViewportFocused)
        {
            m_EditorCamera.OnUpdate(ts);
        }
        
        Render::Renderer2D::ResetStats();
        m_Framebuffer->Bind();
        Render::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        Render::RenderCommand::Clear();
    
        // Update scene
        m_Scene->OnUpdateEditor(ts, m_EditorCamera);    
        m_Framebuffer->Unbind();
    }

    void EditorLayer::OnEvent(Event &e)
    {
        VersaMachina::EventDispatcher dispatcher(e);
        dispatcher.Dispatch<KeyPressedEvent>(VM_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
        if(m_ViewportFocused)
            m_EditorCamera.OnEvent(e);
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
        static ImGuiWindowFlags gizmoWindowFlags = 0;
    	ImGui::Begin("Viewport", nullptr, gizmoWindowFlags);
        {
            m_ViewportFocused = ImGui::IsWindowFocused();
            m_ViewportHovered = ImGui::IsWindowHovered();
            ImGuiWindow* window = ImGui::GetCurrentWindow();
            gizmoWindowFlags = ImGui::IsWindowHovered() && ImGui::IsMouseHoveringRect(window->InnerRect.Min, window->InnerRect.Max) ? ImGuiWindowFlags_NoMove : 0;

            Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

            ImVec2 viewportSize = ImGui::GetContentRegionAvail();
            m_ViewportSize = { viewportSize.x, viewportSize.y };

            uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();

            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Wint-to-pointer-cast" // Ignore warning caused by pointer conversion of int
                ImGui::Image((void*)textureID, viewportSize, ImVec2{0,1}, ImVec2{1,0});
            #pragma GCC diagnostic pop      

            // Gizmos
            ECS::Entity selected = m_SceneHierarchyPanel.GetSelectedEntity();
            if(selected && m_ImGuizmoType!=-1)
            {
                ImGuizmo::SetOrthographic(false);
                ImGuizmo::SetDrawlist();
                float x = ImGui::GetWindowPos().x;
                float y = ImGui::GetWindowPos().y;
                float width = ImGui::GetWindowWidth();
                float height = ImGui::GetWindowHeight();
                ImGuizmo::SetRect(x, y, width, height);
                
                // Camera
//                auto cameraEntity = m_Scene->GetPrimaryCamera();
//                const auto& camera = cameraEntity.GetComponent<ECS::CameraComponent>();
//                const glm::mat4& projection = camera.m_Camera->GetProjectionMatrix();
//                auto& ct = cameraEntity.GetComponent<ECS::TransformComponent>();
//                auto view= glm::inverse(ct.GetTransform());
                auto view = glm::inverse(m_EditorCamera.GetTransform());
                auto& projection = m_EditorCamera.GetProjectionMatrix();
                glm::mat4 idMatrix = glm::mat4{1};
                // Entity transform
                auto& tc = selected.GetComponent<ECS::TransformComponent>();
                auto& transform = tc.GetTransform();
                // Snapping
                bool snap = Input::IsKeyPressed(Key::LeftControl);
                float snapValue = 0.5f;
                if(m_ImGuizmoType == ImGuizmo::OPERATION::ROTATE)
                    snapValue = 45.0f;
                
                float snapValues[3] = {snapValue,snapValue,snapValue};

                ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, width, height);
                ImGuizmo::DrawGrid(glm::value_ptr(view), glm::value_ptr(projection), glm::value_ptr(idMatrix), 100.f);
                ImGuizmo::Manipulate(glm::value_ptr(view), glm::value_ptr(projection), (ImGuizmo::OPERATION)m_ImGuizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform), nullptr, snap ? snapValues : nullptr);
//                ImGuizmo::ViewManipulate(glm::value_ptr(view), 8.f, {(width+x)-128,(height+y)-128}, {128, 128}, 0x10101010); // TODO: Figure this out & fix it
        
                if(ImGuizmo::IsUsing())
                {
                    glm::vec3 translation, rotation, scale;
                    Math::DecomposeTransform(transform, translation, rotation, scale);
                    tc.Transform = transform;
                    tc.Translation = translation;
                    tc.Rotation += (rotation-tc.Rotation);
                    tc.Scale = scale;
                }
            }
        }
        ImGui::End();
        ImGui::PopStyleVar();

        // Simulator
        ImGui::Begin("Simulator");
        ImGui::End();
        // Inspector
        ImGui::Begin("Project");
        ImGui::End();
        // Node Editor
        ImGui::Begin("Node Editor");
        if(ImGui::CollapsingHeader("Node Editor"))
        {
            GraphEditor::EditOptions(m_NodeOptions);
        }
        if(ImGui::Button("Fit All Nodes"))
            m_NodeFit = GraphEditor::Fit_AllNodes;
        if(ImGui::Button("Fit Selected Node"))
            m_NodeFit = GraphEditor::Fit_SelectedNodes;
        GraphEditor::Show(m_NodeDelegate, m_NodeOptions, m_NodeViewState, true, &m_NodeFit);
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
            // Gizmos
            case Key::Q:
            {
                m_ImGuizmoType = -1;
                break;
            }
            case Key::W:
            {
                m_ImGuizmoType = ImGuizmo::OPERATION::TRANSLATE;
                break;
            }
            case Key::E:
            {
                m_ImGuizmoType = ImGuizmo::OPERATION::SCALE;
                break;
            }
            case Key::R:
            {
                m_ImGuizmoType = ImGuizmo::OPERATION::ROTATE;
                break;
            }
        }
        return false;
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

