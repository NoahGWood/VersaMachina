#pragma once

#include "Render/BufferLayout.h"

namespace VersaMachina
{
    namespace Render
    {
        class VertexBuffer
        {
            public:
                virtual ~VertexBuffer() = default;

                virtual void Bind() const = 0;
                virtual void UnBind() const = 0;

                virtual void SetData(uint32_t size, const void* data) = 0;

                virtual const BufferLayout& GetLayout() const = 0;
                virtual void SetLayout(const BufferLayout& layout) = 0;

                static Ref<VertexBuffer> Create(uint32_t size);
                static Ref<VertexBuffer> Create(uint32_t size, float* vertices);
        };
    } // namespace Render
    
} // namespace VersaMachina
