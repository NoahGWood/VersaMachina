#include "pch.h"
#include "OpenGL/include/OpenGLBuffer.h"
#include "Render/VertexBuffer.h"
#include "Render/IndexBuffer.h"

#include "glad/glad.h"

namespace VersaMachina
{
    namespace Render
    {
        OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size, float* vertices)
        {
            glCreateBuffers(1, &m_RendererID);
            glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
            glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
        }

        OpenGLVertexBuffer::~OpenGLVertexBuffer()
        {
            glDeleteBuffers(1, &m_RendererID);
        }

        void OpenGLVertexBuffer::Bind() const
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        }
        void OpenGLVertexBuffer::UnBind() const
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        // Index buffer
        OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t count, uint32_t* indices)
            : m_Count(count)
        {
            glCreateBuffers(1, &m_RendererID);
            Bind();
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
        }
        OpenGLIndexBuffer::~OpenGLIndexBuffer()
        {
            glDeleteBuffers(1, &m_RendererID);
        }      
        void OpenGLIndexBuffer::Bind() const
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        }
        void OpenGLIndexBuffer::UnBind() const
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    } // namespace Render
    
} // namespace VersaMachina
