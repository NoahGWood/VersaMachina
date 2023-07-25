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
        		virtual void OnImGuiRender() override;
        
        		void Begin();
        		void End();

    	private:
    		float m_Time = 0.0f;

        };
    } // namespace UI
    
} // namespace VersaMachina

