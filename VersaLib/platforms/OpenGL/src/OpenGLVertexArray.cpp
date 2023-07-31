#include "pch.h"
#include "OpenGL/include/OpenGLVertexArray.h"

#include <glad/glad.h>

namespace VersaMachina
{
    namespace Render
    {

        static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
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

        OpenGLVertexArray::OpenGLVertexArray()
        {
            VM_PROFILE_FUNCTION();

            glCreateVertexArrays(1, &m_RendererID);
        }
        OpenGLVertexArray::~OpenGLVertexArray()
        {
            VM_PROFILE_FUNCTION();

            glDeleteVertexArrays(1, &m_RendererID);
        }

        void OpenGLVertexArray::Bind() const
        {
            VM_PROFILE_FUNCTION();

            glBindVertexArray(m_RendererID);
        }
        void OpenGLVertexArray::UnBind() const
        {
            VM_PROFILE_FUNCTION();

            glBindVertexArray(0);
        }
        void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
        {
            VM_PROFILE_FUNCTION();
    
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
                    ShaderDataTypeToOpenGLBaseType(element.Type),
                    element.Normalized ? GL_TRUE : GL_FALSE,
                    layout.GetStride(),
                    (const void*)element.Offset
                );
                index++;
            }
            #pragma GCC diagnostic pop

            m_VertexBuffers.push_back(vertexBuffer);
        }
        void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
        {
            VM_PROFILE_FUNCTION();

            glBindVertexArray(m_RendererID);
            indexBuffer->Bind();

            m_IndexBuffer = indexBuffer;
        }

    } // namespace Render
    
} // namespace VersaMachina
