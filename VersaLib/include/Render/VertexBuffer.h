#pragma once

#include "Render/BufferLayout.h"

namespace VersaMachina
{
    namespace Render
    {
        class VertexBuffer
        {
            public:
                virtual ~VertexBuffer() {}

                virtual void Bind() const = 0;
                virtual void UnBind() const = 0;

                virtual void SetLayout(const BufferLayout& layout) = 0;

                virtual const BufferLayout& GetLayout() const = 0;

                static VertexBuffer* Create(uint32_t size, float* vertices);
        };
    } // namespace Render
    
} // namespace VersaMachina
