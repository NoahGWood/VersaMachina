#pragma once
#include "Events/Event.h"

#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"
#include "Events/WindowEvent.h"

namespace VersaMachina
{
    class Layer
    {
        public:
            Layer(const std::string & name = "Layer");
        	virtual ~Layer();
        
            virtual void OnAttach() {}
            virtual void OnDetach() {}
            virtual void OnUpdate() {}

            virtual void OnEvent(Event& event) {}
            

            inline const std::string& GetName() const {return m_DebugName; }

            virtual bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e) { return false; }
    		virtual bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e) { return false; }
    		virtual bool OnMouseMovedEvent(MouseMovedEvent& e) { return false; }
    		virtual bool OnMouseScrolledEvent(MouseScrolledEvent& e) { return false; }
    		virtual bool OnKeyPressedEvent(KeyPressedEvent& e) { return false; }
    		virtual bool OnKeyReleasedEvent(KeyReleasedEvent& e) { return false; }
    		virtual bool OnKeyTypedEvent(KeyTypedEvent& e) { return false; }
    		virtual bool OnWindowResizedEvent(WindowResizedEvent& e) { return false; }

        protected:
            std::string m_DebugName;
    };
} // namespace VersaMachina
