#include "pch.h"
#include "OpenGL/include/OpenGLBuffer.h"
#include "Render/VertexBuffer.h"
#include "Render/IndexBuffer.h"

#include <glad/glad.h>

namespace VersaMachina
{
    namespace Render
    {
        OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
        {
            VM_PROFILE_FUNCTION();

            glCreateBuffers(1, &m_RendererID);
            glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
            glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
        }
        OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size, float* vertices)
        {
            VM_PROFILE_FUNCTION();

            glCreateBuffers(1, &m_RendererID);
            glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
            glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
        }

        OpenGLVertexBuffer::~OpenGLVertexBuffer()
        {
            VM_PROFILE_FUNCTION();

            glDeleteBuffers(1, &m_RendererID);
        }
        void OpenGLVertexBuffer::SetData(uint32_t size, const void* data)
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
            glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
        }
        void OpenGLVertexBuffer::Bind() const
        {
            VM_PROFILE_FUNCTION();

            glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        }
        void OpenGLVertexBuffer::UnBind() const
        {
            VM_PROFILE_FUNCTION();

            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        // Index buffer
        OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t count, uint32_t* indices)
            : m_Count(count)
        {
            VM_PROFILE_FUNCTION();

            glCreateBuffers(1, &m_RendererID);
            glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
            glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
            Bind();
        }
        OpenGLIndexBuffer::~OpenGLIndexBuffer()
        {
            VM_PROFILE_FUNCTION();

            glDeleteBuffers(1, &m_RendererID);
        }      
        void OpenGLIndexBuffer::Bind() const
        {
            VM_PROFILE_FUNCTION();

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        }
        void OpenGLIndexBuffer::UnBind() const
        {
            VM_PROFILE_FUNCTION();

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    } // namespace Render
    
} // namespace VersaMachina
