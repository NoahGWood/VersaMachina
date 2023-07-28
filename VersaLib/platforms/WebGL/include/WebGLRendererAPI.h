# pragma once

#include "Render/RendererAPI.h"

namespace VersaMachina
{
    namespace Render
    {
        class WebGLRendererAPI : public RendererAPI
        {
            public:
                virtual void SetClearColor(const glm::vec4& color) override;
                virtual void Clear() override;

                virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
        };
    } // namespace Render
        
} // namespace VersaMachina
