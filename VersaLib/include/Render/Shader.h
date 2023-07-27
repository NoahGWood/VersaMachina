#pragma once

#include <string>
#include <glm/glm.hpp>

namespace VersaMachina
{
    namespace Render
    {
        class Shader
        {
            public:
                Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
                ~Shader();

                virtual void Bind() const;
                virtual void UnBind() const;

                void UploadUniformMat4(const std::string name, const glm::mat4& matrix);
            private:
                uint32_t m_RendererID;

        };
    } // namespace Render
    
} // namespace VersaMachina
