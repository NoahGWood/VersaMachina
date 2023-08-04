#pragma once

#include "Versa.h"

class EditorLayer : public VersaMachina::Layer
{
    public:
        EditorLayer();
        ~EditorLayer() = default;
        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnEvent(VersaMachina::Event &e) override;
        virtual void OnUpdate(VersaMachina::Timestep ts) override;
    	virtual void OnImGuiRender() override;


    private:
        // Scene Management
        VersaMachina::Ref<VersaMachina::Scenes::Scene> m_Scene;
        // Viewport
        VersaMachina::Camera::CameraController m_CameraController;
        VersaMachina::Ref<VersaMachina::Render::Framebuffer> m_Framebuffer;
        glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
        bool m_ViewportFocused=false, m_ViewportHovered=false;
            // Temporary
            VersaMachina::Ref<VersaMachina::Render::Shader> m_Shader;
            VersaMachina::Ref<VersaMachina::Render::VertexArray> m_VertexArray;
            VersaMachina::Ref<VersaMachina::Render::IndexBuffer> m_IndexBuffer;
            VersaMachina::Ref<VersaMachina::Render::VertexBuffer> m_VertexBuffer;
            VersaMachina::Ref<VersaMachina::Render::Texture2D> m_CheckerboardTexture;
            glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 0.5f};
};