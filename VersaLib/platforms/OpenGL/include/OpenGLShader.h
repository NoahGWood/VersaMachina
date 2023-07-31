#pragma once

#include "Render/Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

//TODO
typedef unsigned int GLenum;

namespace VersaMachina
{
    namespace Render
    {
        class OpenGLShader : public Shader
        {
            public:
                OpenGLShader(const std::string& filepath);
                OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
                virtual ~OpenGLShader();

                virtual void Bind() const override;
                virtual void UnBind() const override;

                virtual const std::string& GetName() const override { return m_Name; }
                virtual void SetName(std::string name) override { m_Name = name; }

                virtual void SetInt(const std::string& name, const int& value) override { VM_PROFILE_FUNCTION(); UploadUniformInt(name, value); };

                virtual void SetFloat(const std::string& name, const float& value) override { VM_PROFILE_FUNCTION(); UploadUniformFloat(name, value);    };
                virtual void SetFloat2(const std::string& name, const glm::vec2& value) override { VM_PROFILE_FUNCTION(); UploadUniformFloat2(name, value); }
                virtual void SetFloat3(const std::string& name, const glm::vec3& value) override { VM_PROFILE_FUNCTION(); UploadUniformFloat3(name, value); }
                virtual void SetFloat4(const std::string& name, const glm::vec4& value) override { VM_PROFILE_FUNCTION(); UploadUniformFloat4(name, value); }

                virtual void SetMat3(const std::string& name, const glm::mat3& matrix) override { VM_PROFILE_FUNCTION(); UploadUniformMat3(name, matrix); }
                virtual void SetMat4(const std::string& name, const glm::mat4& matrix) override { VM_PROFILE_FUNCTION(); UploadUniformMat4(name, matrix); }

                void UploadUniformInt(const std::string& name, const int& value);

                void UploadUniformFloat(const std::string& name, const float& value);
                void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
                void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
                void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

                void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
                void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
                
            private:
                std::string ReadFile(const std::string& filepath);
                std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
                void Compile(const std::unordered_map<GLenum, std::string> shaderSources);
            private:
                uint32_t m_RendererID;
                std::string m_Name;

        };
    } // namespace Render
    
} // namespace VersaMachina
