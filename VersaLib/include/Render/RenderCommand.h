#pragma once
#include "Render/RendererAPI.h"

namespace VersaMachina
{
    namespace Render
    {
        class RenderCommand
        {
            public:
                inline static void Init() { s_RendererAPI->Init(); }
                inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
                {
                    s_RendererAPI->SetViewport(x,y,width,height);
                }
                inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) { s_RendererAPI->DrawIndexed(vertexArray); }
                inline static void Clear() { s_RendererAPI->Clear(); }
                inline static void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }
            private:
                static Scope<RendererAPI> s_RendererAPI;
        };
    } // namespace Render
    
} // namespace VersaMachina
