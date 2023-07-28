#pragma once

#include "Render/Shader.h"

namespace VersaMachina
{
    namespace Render
    {
        class WebGLShader
        {
            public:
                WebGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
                ~WebGLShader();

                virtual void Bind() const;
                virtual void UnBind() const;

            private:
                uint32_t m_RendererID;

        };
    } // namespace Render
    
} // namespace VersaMachina
