#pragma once

#include <string>

namespace VersaMachina
{
    namespace Render
    {
        class Shader
        {
            public:
                virtual ~Shader() = default;

                virtual void Bind() const = 0;
                virtual void UnBind() const = 0;

                static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
        };
    } // namespace Render
    
} // namespace VersaMachina
