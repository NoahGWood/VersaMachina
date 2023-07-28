#include "pch.h"
#include "WebGL/include/WebGLVertexArray.h"

#include <glad/glad.h>

namespace VersaMachina
{
    namespace Render
    {

        static GLenum ShaderDataTypeToWebGLBaseType(ShaderDataType type)
        {
            switch(type)
            {
                case ShaderDataType::Float:  return GL_FLOAT;
                case ShaderDataType::Float2: return GL_FLOAT;
                case ShaderDataType::Float3: return GL_FLOAT;
                case ShaderDataType::Float4: return GL_FLOAT;
                case ShaderDataType::Mat3:   return GL_FLOAT;
                case ShaderDataType::Mat4:   return GL_FLOAT;
                case ShaderDataType::Int:    return GL_INT;
                case ShaderDataType::Int2:   return GL_INT;
                case ShaderDataType::Int3:   return GL_INT;
                case ShaderDataType::Int4:   return GL_INT;
                case ShaderDataType::Bool:   return GL_BOOL;
            }
            VM_CORE_ASSERT(false, "Unknown ShaderDataType!");
            return 0;
        }

        WebGLVertexArray::WebGLVertexArray()
        {
            glCreateVertexArrays(1, &m_RendererID);
        }
        WebGLVertexArray::~WebGLVertexArray()
        {
            glDeleteVertexArrays(1, &m_RendererID);
        }

        void WebGLVertexArray::Bind() const
        {
            glBindVertexArray(m_RendererID);
        }
        void WebGLVertexArray::UnBind() const
        {
            glBindVertexArray(0);
        }
        void WebGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
        {
            glBindVertexArray(m_RendererID);
            vertexBuffer->Bind();

            uint32_t index=0;
            const auto& layout = vertexBuffer->GetLayout();
            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Wint-to-pointer-cast" // Ignore warning caused by pointer conversion of int
            for (const auto& element : layout)
            {
                glEnableVertexAttribArray(index);
                glVertexAttribPointer(
                    index, element.GetComponentCount(), 
                    ShaderDataTypeToWebGLBaseType(element.Type),
                    element.Normalized ? GL_TRUE : GL_FALSE,
                    layout.GetStride(),
                    (const void*)element.Offset
                );
                index++;
            }
            #pragma GCC diagnostic pop

            m_VertexBuffers.push_back(vertexBuffer);
        }
        void WebGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
        {
            glBindVertexArray(m_RendererID);
            indexBuffer->Bind();

            m_IndexBuffer = indexBuffer;
        }

    } // namespace Render
    
} // namespace VersaMachina
