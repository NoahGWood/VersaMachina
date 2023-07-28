#pragma once

#include "Core/Input.h"

namespace VersaMachina
{
    namespace Input
    {
        class WebGLInput : public Input
        {
            protected:
                virtual bool IsKeyPressedImpl(int keycode) override;

                // Mouse
                virtual bool IsButtonPressedImpl(int keycode) override;
                virtual std::pair<float, float> GetMousePosImpl() override;
                virtual float GetMouseXImpl() override;
                virtual float GetMouseYImpl() override;

        };
    } // namespace Input
    
} // namespace VersaMachina
