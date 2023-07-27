#pragma once

#include "Render/Shader.h"

namespace VersaMachina
{
    namespace Render
    {
        class OpenGLShader
        {
            public:
                OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
                ~OpenGLShader();

                virtual void Bind() const;
                virtual void UnBind() const;

            private:
                uint32_t m_RendererID;

        };
    } // namespace Render
    
} // namespace VersaMachina
