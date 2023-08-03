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

}
void EditorLayer::OnDetach()
{
}
void EditorLayer::OnUpdate(VersaMachina::Timestep ts)
{
    VM_PROFILE_FUNCTION()

    static float rotation = 0.0f;
    rotation += ts * 5.0f;
    // Reset statistics
    VersaMachina::Render::Renderer2D::ResetStats();

    // Update
    {    
        VM_PROFILE_SCOPE("Renderer Prep");
        m_Framebuffer->Bind();
        VersaMachina::Render::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        VersaMachina::Render::RenderCommand::Clear();
    }    
    VersaMachina::Render::Renderer2D::BeginScene(m_CameraController.GetCamera()); // camera, lights, environment);
	
    VersaMachina::Render::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
    VersaMachina::Render::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, m_SquareColor);
    VersaMachina::Render::Renderer2D::DrawQuad({ -0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.82f, 0.3f, 0.8f, 1.0f });
//    VersaMachina::Render::Renderer2D::DrawQuad({ 0.0f, 0.0f}, { 20.0f, 20.0f }, m_CheckerboardTexture, m_SquareColor);
    VersaMachina::Render::Renderer2D::DrawQuad({-0.5f, -0.5f, -0.1f }, glm::vec2(5.0f), glm::vec3(rotation), glm::vec3(0.0f), m_CheckerboardTexture, 10, m_SquareColor);
    
    VersaMachina::Render::Renderer2D::EndScene();

    VersaMachina::Render::Renderer2D::BeginScene(m_CameraController.GetCamera()); // camera, lights, environment);
    for(float y = -5.0f; y< 5.0f; y+=0.5f)
    {
        for(float x = -5.0f; x<5.0f; x+=0.5f)
        {
            glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.8f};            
            VersaMachina::Render::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
        }
    }
    VersaMachina::Render::Renderer2D::EndScene();
    
//    m_CameraController.OnUpdate(ts);
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
    ImVec2 viewportSize = ImGui::GetContentRegionAvail();
    if(m_ViewportSize != *(glm::vec2*)&viewportSize)
    {
        m_ViewportSize = { viewportSize.x, viewportSize.y };
        m_Framebuffer->Resize(m_ViewportSize.x, m_ViewportSize.y);

        m_CameraController.Resize(m_ViewportSize.x, m_ViewportSize.y);
    }

    uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
    ImGui::Image((void*)textureID, viewportSize, ImVec2{0,1}, ImVec2{1,0});
	ImGui::End();
    ImGui::PopStyleVar();
    // Viewport
}