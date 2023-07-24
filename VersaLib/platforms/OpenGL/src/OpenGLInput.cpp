#include "pch.h"
#include "OpenGL/include/OpenGLInput.h"

#include "Core/Application.h"
#include <GLFW/glfw3.h>

namespace VersaMachina
{
    namespace Input
    {
        Input* Input::s_Instance = new OpenGLInput();

        bool OpenGLInput::IsKeyPressedImpl(int keycode)
        {
            auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
            auto state = glfwGetKey(window, keycode);
            return state == GLFW_PRESS || state == GLFW_REPEAT;
        }
        bool OpenGLInput::IsButtonPressedImpl(int button)
        {
            auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
            auto state = glfwGetMouseButton(window, button);
            return state == GLFW_PRESS;
        }

        float OpenGLInput::GetMouseXImpl()
        {
            auto[x,y]=GetMousePosImpl();
            return x;
        }
        float OpenGLInput::GetMouseYImpl()
        {
            auto[x,y]=GetMousePosImpl();
            return x;
        }
        std::pair<float, float> OpenGLInput::GetMousePosImpl()
        {
            auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            return {(float)xpos, (float)ypos};
        }
    } // namespace Input

} // namespace VersaMachina
