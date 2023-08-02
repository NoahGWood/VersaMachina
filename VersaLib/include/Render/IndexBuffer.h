#pragma once

namespace VersaMachina
{
    namespace Render
    {
        class IndexBuffer
        {
            public:
                virtual ~IndexBuffer() = default;

                virtual void Bind() const = 0;
                virtual void UnBind() const = 0;

                virtual uint32_t GetCount() const = 0;

                static Ref<IndexBuffer> Create(uint32_t count, uint32_t* indices);
        };
    } // namespace Render
    
} // namespace VersaMachina
