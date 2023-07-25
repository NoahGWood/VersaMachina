# Render Context API

## Purpose
The Render Context API is an abstraction API that allows VersaMachina to create and use windows that target different platforms and graphics backends with our Rendering API without having to use platform-specific code within the engine and editor itself.

## Implementation
The Render Context API is implemented as a simple base class called RenderContext and implements the following virtual functions that you will need to implement if you wish to support a new platform:

- **Init()**
    - Init() is used to register the window context with the appropriate backend. 
- **SwapBuffers()**
    - SwapBuffers() is called when rendering has completed and tells the backend to swap the front buffer with the back buffer.

## RenderContext Header:

```
#pragma once

namespace VersaMachina
{
    namespace Render
    {
        class RenderContext
        {
            public:
                RenderContext();
                ~RenderContext();

                virtual void Init() = 0;
                virtual void SwapBuffers() = 0;


            private:

            protected:


        };
    } // namespace Render
    
} // namespace VersaMachina

```
## Examples:
### OpenGL Implementation

#### OpenGLRenderContext.h
```
#pragma once

#include "Render/RenderContext.h"

class GLFWwindow;

namespace VersaMachina
{
    namespace Render
    {
        class OpenGLRenderContext : public RenderContext
        {
            public:
                OpenGLRenderContext(GLFWwindow* windowHandle);
                virtual void Init() override;
                virtual void SwapBuffers() override;
            private:
                GLFWwindow* m_WindowHandle;

        };
    } // namespace Render
    
} // namespace VersaMachina
```
#### OpenGLRenderContext.cpp
```
#include "pch.h"
#include "OpenGL/include/OpenGLRenderContext.h"

#include <glad/glad.h>
#include "GLFW/glfw3.h"

namespace VersaMachina
{
    namespace Render
    {
        OpenGLRenderContext::OpenGLRenderContext(GLFWwindow* windowHandle)
            : m_WindowHandle(windowHandle)
        {
            VM_CORE_ASSERT(windowHandle, "Window handle is null!");
        }

        void OpenGLRenderContext::Init()
        {
            glfwMakeContextCurrent(m_WindowHandle);
            // Setup Glad
            int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            VM_CORE_ASSERT(status, "Failed to initialize glad.");        
        }

        void OpenGLRenderContext::SwapBuffers()
        {
            glfwSwapBuffers(m_WindowHandle);

        }
    } // namespace Render
    
} // namespace VersaMachina
```