#pragma once
#include "Core/Base.h"

namespace VersaMachina
{
    namespace Render
    {
        class UniformBuffer
        {
        private:
            /* data */
        public:

            virtual ~UniformBuffer() {}
            virtual void SetData(const void* data, uint32_t size, uint32_t offset=0) = 0;

            static Ref<UniformBuffer> Create(uint32_t size, uint32_t binding);
        };        
        
    } // namespace Render
    
} // namespace VersaMachina
