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
        Ref<ECS::Scene> m_Scene;
        std::string m_SceneFile;
        // ECS::Entity m_SquareEntity;
        // Camera::Camera* m_Camera;
        // ECS::Entity m_CameraEntity;
        Ref<Render::Framebuffer> m_Framebuffer;
        glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
        bool m_ViewportFocused=false, m_ViewportHovered=false;
        // Panels
        SceneHierarchyPanel m_SceneHierarchyPanel;
    private:
        bool OnKeyPressed(VersaMachina::KeyPressedEvent& e);
        void NewScene();
        void Open();
        void Save();
        void SaveAs();
    };    
} // namespace VersaMachina

