#include "pch.h"
#include "OpenGL/include/OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace VersaMachina
{
    void OpenGLMessageCallback(
	unsigned source,
	unsigned type,
	unsigned id,
	unsigned severity,
	int length,
	const char* message,
	const void* userParam)
	{
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:         VM_CORE_CRITICAL(message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:       VM_CORE_ERROR(message); return;
			case GL_DEBUG_SEVERITY_LOW:          VM_CORE_WARN(message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: VM_CORE_TRACE(message); return;
		}
		
		VM_CORE_ASSERT(false, "Unknown severity level!");
	}

    namespace Render
    {
        
        void OpenGLRendererAPI::Init()
        {
            #ifdef VM_DEBUG
                glEnable(GL_DEBUG_OUTPUT);
                glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
                glDebugMessageCallback(OpenGLMessageCallback, nullptr);

                glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
            #endif
            
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glEnable(GL_DEPTH_TEST);
            glEnable(GL_LINE_SMOOTH);
        }
        void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
        {
            glClearColor(color.r, color.g, color.b, color.a);
        }

        void OpenGLRendererAPI::Clear()
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
        {
            VM_PROFILE_FUNCTION();
//       		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
//    		uint32_t count = indexCount ? vertexArray->GetIndexBuffer()->GetCount() : indexCount;
    		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
    		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
        {
            glViewport(x, y, width, height);
        }

    } // namespace Render
    
} // namespace VersaMachina
