#include "EditorLayer.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

EditorLayer::EditorLayer()
    : Layer("EditorLayer"), m_CameraController()
{
    
}

void EditorLayer::OnAttach()
{
	m_CheckerboardTexture = VersaMachina::Render::Texture2D::Create("VersaEditor/assets/textures/Checkerboard.png");

    VersaMachina::Render::FramebufferSpecification fbSpec;
    fbSpec.Width = 1280;
    fbSpec.Height = 720;
    m_Framebuffer = VersaMachina::Render::Framebuffer::Create(fbSpec);

    m_Scene = VersaMachina::CreateRef<VersaMachina::Scenes::Scene>();

    VersaMachina::Scenes::Entity squareEntity = m_Scene->CreateEntity("Square");
    squareEntity.AddComponent<VersaMachina::Scenes::SpriteRendererComponent>(glm::vec4{0.0f, 1.0f, 0.0f, 1.0f});
}
void EditorLayer::OnDetach()
{
}
void EditorLayer::OnUpdate(VersaMachina::Timestep ts)
{
    VM_PROFILE_FUNCTION();


    VersaMachina::Render::FramebufferSpecification spec = m_Framebuffer->GetSpecification();
	if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
		(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
	{
		m_Framebuffer->Resize(m_ViewportSize.x, m_ViewportSize.y);
		m_CameraController.Resize(m_ViewportSize.x, m_ViewportSize.y);
	}

    // Update camera
    if(m_ViewportFocused)
        m_CameraController.OnUpdate(ts);

    VersaMachina::Render::Renderer2D::ResetStats();
    m_Framebuffer->Bind();    
    VersaMachina::Render::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    VersaMachina::Render::RenderCommand::Clear();
    
    VersaMachina::Render::Renderer2D::BeginScene(m_CameraController.GetCamera()); // camera, lights, environment);
    // Update scene
    m_Scene->OnUpdate(ts);
    VersaMachina::Render::Renderer2D::EndScene();
    
    m_Framebuffer->Unbind();
}

void EditorLayer::OnEvent(VersaMachina::Event &e)
{
    m_CameraController.OnEvent(e);
}


void EditorLayer::OnImGuiRender()
{
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

	ImGui::Begin("Settings");

    auto stats = VersaMachina::Render::Renderer2D::GetStats();

    ImGui::ColorEdit4("Square color", glm::value_ptr(m_SquareColor));
    ImGui::Text("Renderer 2D Stats:");
    ImGui::Text("Draw Calls: %d", stats.DrawCalls);
    ImGui::Text("Quads: %d", stats.QuadCount);
    ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
    ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::End();

    // Viewport
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0,0});
	ImGui::Begin("Viewport");
        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();
        VersaMachina::Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);
    
        ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        m_ViewportSize = { viewportSize.x, viewportSize.y };

        uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();

        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wint-to-pointer-cast" // Ignore warning caused by pointer conversion of int
            ImGui::Image((void*)textureID, viewportSize, ImVec2{0,1}, ImVec2{1,0});
        #pragma GCC diagnostic pop      
    ImGui::End();
    ImGui::PopStyleVar();
}