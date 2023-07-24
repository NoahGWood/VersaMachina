#pragma once

#include "Core/Layer.h"


namespace VersaMachina
{
    namespace UI
    {
        class ImGUILayer : public Layer
        {
            public:
                ImGUILayer();
                ~ImGUILayer();
 
                void OnAttach() override;
                void OnDetach() override;
                void OnUpdate() override;

                void OnEvent(Event& event) override;           
    
        		virtual bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e) override;
        		virtual bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e) override;
        		virtual bool OnMouseMovedEvent(MouseMovedEvent& e) override;
        		virtual bool OnMouseScrolledEvent(MouseScrolledEvent& e) override;
        		virtual bool OnKeyPressedEvent(KeyPressedEvent& e) override;
        		virtual bool OnKeyReleasedEvent(KeyReleasedEvent& e) override;
        		virtual bool OnKeyTypedEvent(KeyTypedEvent& e) override;
        		virtual bool OnWindowResizedEvent(WindowResizedEvent& e) override;
    	private:
    		float m_Time = 0.0f;

        };
    } // namespace UI
    
} // namespace VersaMachina

