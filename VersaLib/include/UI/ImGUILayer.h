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
 
                virtual void OnAttach() override;
                virtual void OnDetach() override;
        		virtual void OnImGuiRender() override;
        		virtual void OnEvent(Event& e) override;
        
        		void Begin();
        		void End();

    	private:
    		float m_Time = 0.0f;

        };
    } // namespace UI
    
} // namespace VersaMachina

