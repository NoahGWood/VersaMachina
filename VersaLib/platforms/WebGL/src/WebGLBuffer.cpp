#include "pch.h"
#include "WebGL/include/WebGLBuffer.h"
#include "Render/VertexBuffer.h"
#include "Render/IndexBuffer.h"

#include "glad/glad.h"

namespace VersaMachina
{
    namespace Render
    {
        WebGLVertexBuffer::WebGLVertexBuffer(uint32_t size, float* vertices)
        {
            glCreateBuffers(1, &m_RendererID);
            glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
            glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
        }

        WebGLVertexBuffer::~WebGLVertexBuffer()
        {
            glDeleteBuffers(1, &m_RendererID);
        }

        void WebGLVertexBuffer::Bind() const
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        }
        void WebGLVertexBuffer::UnBind() const
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        // Index buffer
        WebGLIndexBuffer::WebGLIndexBuffer(uint32_t count, uint32_t* indices)
            : m_Count(count)
        {
            glCreateBuffers(1, &m_RendererID);
            Bind();
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
        }
        WebGLIndexBuffer::~WebGLIndexBuffer()
        {
            glDeleteBuffers(1, &m_RendererID);
        }      
        void WebGLIndexBuffer::Bind() const
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        }
        void WebGLIndexBuffer::UnBind() const
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    } // namespace Render
    
} // namespace VersaMachina
