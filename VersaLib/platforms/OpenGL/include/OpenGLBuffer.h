#pragma once
#include "Render/VertexBuffer.h"
#include "Render/IndexBuffer.h"

namespace VersaMachina
{
    namespace Render
    {
        class OpenGLVertexBuffer : public VertexBuffer
        {
            public:
                OpenGLVertexBuffer(uint32_t size, float* vertices);
                virtual ~OpenGLVertexBuffer();
                virtual void Bind() const override;
                virtual void UnBind() const override;

                virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
                virtual const BufferLayout& GetLayout() const  override { return m_Layout; }
           
            private:
                uint32_t m_RendererID;
                BufferLayout m_Layout;
        };

        class OpenGLIndexBuffer : public IndexBuffer
        {
            public:
                OpenGLIndexBuffer(uint32_t size, uint32_t* indices);
                virtual ~OpenGLIndexBuffer();

                virtual void Bind() const override;
                virtual void UnBind() const override;

                virtual uint32_t GetCount() const override { return m_Count; }

            private:
                uint32_t m_RendererID;
                uint32_t m_Count;
        };
    } // namespace Render
    
} // namespace VersaMachina
