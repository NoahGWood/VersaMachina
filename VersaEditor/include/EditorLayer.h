#pragma once

#include "Versa.h"

#include "panels/SceneHierarchyPanel.h"

namespace VersaMachina
{
class EditorLayer : public Layer
{
    public:
        EditorLayer();
        ~EditorLayer() = default;
        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnEvent(Event &e) override;
        virtual void OnUpdate(Timestep ts) override;
    	virtual void OnImGuiRender() override;


    private:
        // Scene Management
        Ref<Scenes::Scene> m_Scene;
        Scenes::Entity m_SquareEntity;
        Camera::Camera* m_Camera;
        Scenes::Entity m_CameraEntity;
        // Viewport
        Camera::CameraController m_CameraController;
        Ref<Render::Framebuffer> m_Framebuffer;
        glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
        bool m_ViewportFocused=false, m_ViewportHovered=false;
            // Temporary
            Ref<Render::Shader> m_Shader;
            Ref<Render::VertexArray> m_VertexArray;
            Ref<Render::IndexBuffer> m_IndexBuffer;
            Ref<Render::VertexBuffer> m_VertexBuffer;
            Ref<Render::Texture2D> m_CheckerboardTexture;
            glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 0.5f};

            // Panels
            SceneHierarchyPanel m_SceneHierarchyPanel;
};    
} // namespace VersaMachina

