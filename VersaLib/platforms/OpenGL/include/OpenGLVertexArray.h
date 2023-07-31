#pragma once

#include "Render/VertexArray.h"

namespace VersaMachina
{
    namespace Render
    {
        class OpenGLVertexArray: public VertexArray
        {
            public:
                OpenGLVertexArray();
                virtual ~OpenGLVertexArray() override;

                virtual void Bind() const override;
                virtual void UnBind() const override;

                virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
                virtual void SetIndexBuffer(const  Ref<IndexBuffer>& indexBuffer) override;

                virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { VM_PROFILE_FUNCTION(); return m_VertexBuffers; }
                virtual const Ref<IndexBuffer>& GetIndexBuffer() const { VM_PROFILE_FUNCTION(); return m_IndexBuffer; }


            private:
                uint32_t m_RendererID;
                std::vector<Ref<VertexBuffer>> m_VertexBuffers;
                Ref<IndexBuffer> m_IndexBuffer;

        };
    } // namespace Render
    
} // namespace VersaMachina
