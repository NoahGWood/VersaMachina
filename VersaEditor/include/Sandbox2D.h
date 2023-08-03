#pragma once

#include "Versa.h"

class Sandbox2D : public VersaMachina::Layer
{
    public:
        Sandbox2D();
        ~Sandbox2D() = default;
        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnEvent(VersaMachina::Event &e) override;
        virtual void OnUpdate(VersaMachina::Timestep ts) override;
    	virtual void OnImGuiRender() override;


    private:
        VersaMachina::Camera::CameraController m_CameraController;

        // Temporary
        VersaMachina::Ref<VersaMachina::Render::Shader> m_Shader;
        VersaMachina::Ref<VersaMachina::Render::VertexArray> m_VertexArray;
        VersaMachina::Ref<VersaMachina::Render::IndexBuffer> m_IndexBuffer;
        VersaMachina::Ref<VersaMachina::Render::VertexBuffer> m_VertexBuffer;
        VersaMachina::Ref<VersaMachina::Render::Texture2D> m_CheckerboardTexture;

        glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 0.5f};
};