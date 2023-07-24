#pragma once

#include "Core/KeyCodes.h"

namespace VersaMachina
{
    namespace Input
    {
        class Input 
        {
            public:
                inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); };
                inline static bool IsButtonPressed(int button) { return s_Instance->IsButtonPressedImpl(button); }
                inline static std::pair<float, float> GetMousePos() {  return s_Instance->GetMousePosImpl();}
                inline static float GetMouseX() {  return s_Instance->GetMouseXImpl();}
                inline static float GetMouseY() {  return s_Instance->GetMouseYImpl();}
            private:
                static Input* s_Instance;

            protected:
                virtual bool IsKeyPressedImpl(int keycode) = 0;
                virtual bool IsButtonPressedImpl(int keycode) = 0;
                virtual std::pair<float, float> GetMousePosImpl() = 0;
                virtual float GetMouseXImpl() = 0;
                virtual float GetMouseYImpl() = 0;
        };
    } // namespace Input
       
} // namespace VersaMachina
