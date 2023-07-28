#include "pch.h"
#include "WebGL/include/WebGLInput.h"

#include "Core/Application.h"
#include <GLFW/glfw3.h>

namespace VersaMachina
{
    namespace Input
    {
        Input* Input::s_Instance = new WebGLInput();

        bool WebGLInput::IsKeyPressedImpl(int keycode)
        {
            auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
            auto state = glfwGetKey(window, keycode);
            return state == GLFW_PRESS || state == GLFW_REPEAT;
        }
        bool WebGLInput::IsButtonPressedImpl(int button)
        {
            auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
            auto state = glfwGetMouseButton(window, button);
            return state == GLFW_PRESS;
        }

        float WebGLInput::GetMouseXImpl()
        {
            auto[x,y]=GetMousePosImpl();
            return x;
        }
        float WebGLInput::GetMouseYImpl()
        {
            auto[x,y]=GetMousePosImpl();
            return x;
        }
        std::pair<float, float> WebGLInput::GetMousePosImpl()
        {
            auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            return {(float)xpos, (float)ypos};
        }
    } // namespace Input

} // namespace VersaMachina
