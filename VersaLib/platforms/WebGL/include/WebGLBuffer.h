#pragma once
#include "Render/VertexBuffer.h"
#include "Render/IndexBuffer.h"

namespace VersaMachina
{
    namespace Render
    {
        class WebGLVertexBuffer : public VertexBuffer
        {
            public:
                WebGLVertexBuffer(uint32_t size, float* vertices);
                virtual ~WebGLVertexBuffer();
                virtual void Bind() const override;
                virtual void UnBind() const override;

                virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
                virtual const BufferLayout& GetLayout() const  override { return m_Layout; }
           
            private:
                uint32_t m_RendererID;
                BufferLayout m_Layout;
        };

        class WebGLIndexBuffer : public IndexBuffer
        {
            public:
                WebGLIndexBuffer(uint32_t size, uint32_t* indices);
                virtual ~WebGLIndexBuffer();

                virtual void Bind() const override;
                virtual void UnBind() const override;

                virtual uint32_t GetCount() const override { return m_Count; }

            private:
                uint32_t m_RendererID;
                uint32_t m_Count;
        };
    } // namespace Render
    
} // namespace VersaMachina
