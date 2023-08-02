#include "pch.h"
#include "OpenGL/include/OpenGLShader.h"
#include "glad/glad.h"
#include <glm/gtc/type_ptr.hpp>

// Temporary
#include <fstream>

namespace VersaMachina
{
    namespace Render
    {
        static GLenum ShaderTypeFromString(const std::string &type)
        {
    		if (type == "vertex")
    			return GL_VERTEX_SHADER;
    		if (type == "fragment" || type == "pixel")
    			return GL_FRAGMENT_SHADER;

    		VM_CORE_ASSERT(false, "Unknown shader type!");
    		return 0;
        }
        
        OpenGLShader::OpenGLShader(const std::string& filepath)
        {
            VM_PROFILE_FUNCTION();                
    
            std::string source = ReadFile(filepath);
            auto shaderSources = PreProcess(source);
            Compile(shaderSources);

            // Extract name from filepath
            auto lastSlash = filepath.find_last_of("/\\");
            lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
            auto lastDot = filepath.rfind('.');
            auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
            m_Name = filepath.substr(lastSlash, count);
        }
        OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
            : m_Name(name)
        {
            VM_PROFILE_FUNCTION();                

            std::unordered_map<GLenum, std::string> sources;
            sources[GL_VERTEX_SHADER] = vertexSrc;
            sources[GL_FRAGMENT_SHADER] = fragmentSrc;
            Compile(sources);
        }
        
        OpenGLShader::~OpenGLShader()
        {
            VM_PROFILE_FUNCTION();                

            glDeleteProgram(m_RendererID);
        }

        void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string> shaderSources)
        {
            VM_PROFILE_FUNCTION();                

            GLuint program = glCreateProgram();

            VM_CORE_ASSERT(shaderSources.size() <= 2, "Shader sources must be 2 or less");
            std::array<GLenum, 2> glShaderIDs;
            int glShaderIDIndex = 0;
            for(auto& kv : shaderSources)
            {
                GLenum type = kv.first;
                const std::string& source = kv.second;
                // Create an empty vertex shader handle
                GLuint shader = glCreateShader(type);
                // Send the shader source code to GL
                // Note that std::string's .c_str is NULL character terminated.
                const GLchar *glSource = (const GLchar *)source.c_str();
                glShaderSource(shader, 1, &glSource, 0);
                // Compile the shader
                glCompileShader(shader);
                GLint isCompiled = 0;
                glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
                if(isCompiled == GL_FALSE)
                {
                    GLint maxLength = 0;
                    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
                    // The maxLength includes the NULL character
                    std::vector<GLchar> infoLog(maxLength);
                    glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
                    // We don't need the shader anymore.
                    glDeleteShader(shader);
                    VM_CORE_ERROR("Shader: {0}, {1}", source, infoLog.data());
                    VM_CORE_ASSERT(false, "Shader compilation failure!");
                    break;
                }
                glAttachShader(program, shader);
                glShaderIDs[glShaderIDIndex++] = shader;
            }

            m_RendererID = program;
            // Link our program
            glLinkProgram(program);

            // Note the different functions here: glGetProgram* instead of glGetShader*.
            GLint isLinked = 0;
            glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
            if (isLinked == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> infoLog(maxLength);
                glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
                
                // We don't need the program anymore.
                glDeleteProgram(program);
                // Don't leak shaders either
                for(auto id : glShaderIDs)
                {
                    glDeleteShader(id);
                }

                // Use the infoLog as you see fit.
                
                VM_CORE_ERROR("Shader failure!");
                VM_CORE_ERROR("{0}", infoLog.data());
                VM_CORE_ASSERT(false, "Shader link failure!");
                // In this simple program, we'll just leave
                return;
            }

            // Always detach shaders after a successful link.
            for(auto id : glShaderIDs)
            {
                glDetachShader(program, id);
            }
        }

        std::string OpenGLShader::ReadFile(const std::string& filepath)
        {
            VM_PROFILE_FUNCTION();                

            std::string result;
            std::ifstream f(filepath, std::ios::in | std::ios::binary);
            if(f)
            {
                f.seekg(0, std::ios::end);
                result.resize(f.tellg());
                f.seekg(0, std::ios::beg);
                f.read(&result[0], result.size());
                f.close();
            } else {
                VM_CORE_ERROR("Could not open file '{0}'", filepath);
            }
            return result;
        }

        std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
        {
            std::unordered_map<GLenum, std::string> shaderSources;

            const char* typeToken = "#type";
            size_t typeTokenLength = strlen(typeToken);
            size_t pos = source.find(typeToken, 0);

            while(pos != std::string::npos)
            {
                size_t eol = source.find_first_of("\r\n", pos);
                VM_CORE_ASSERT(eol != std::string::npos, "Syntax error");
                size_t begin = pos + typeTokenLength + 1;
                std::string type = source.substr(begin, eol - begin);
                VM_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified!");

                size_t nextLinePos = source.find_first_not_of("\r\n", eol);
                pos = source.find(typeToken, nextLinePos);
                shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos,
                    pos -(nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos)
                );
            }
            return shaderSources;
        }

        void OpenGLShader::Bind() const
        {
            VM_PROFILE_FUNCTION();                

            glUseProgram(m_RendererID);
        }
        void OpenGLShader::UnBind() const
        {
            VM_PROFILE_FUNCTION();                

            glUseProgram(0);
        }

        void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
        {
            GLint location = glGetUniformLocation(m_RendererID, name.c_str());
            if(location == -1)
            {
                VM_CORE_CRITICAL("Uniform location {0} not found!", name);
            }
            glUniform4f(location, value.x, value.y, value.z, value.w);
        }
        void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
        {
            GLint location = glGetUniformLocation(m_RendererID, name.c_str());
            if(location == -1)
            {
                VM_CORE_CRITICAL("Uniform location {0} not found!", name);
            }
            glUniform3f(location, value.x, value.y, value.z);

        }
        void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
        {
            GLint location = glGetUniformLocation(m_RendererID, name.c_str());
            if(location == -1)
            {
                VM_CORE_CRITICAL("Uniform location {0} not found!", name);
            }
            glUniform2f(location, value.x, value.y);

        }
        void OpenGLShader::UploadUniformFloat(const std::string& name, const float& value)
        {
            GLint location = glGetUniformLocation(m_RendererID, name.c_str());
            if(location == -1)
            {
                VM_CORE_CRITICAL("Uniform location {0} not found!", name);
            }
            glUniform1f(location, value);
        }

        void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
        {
            GLint location = glGetUniformLocation(m_RendererID, name.c_str());
            if(location == -1)
            {
                VM_CORE_CRITICAL("Uniform location {0} not found!", name);
                return;
            }
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
        }
        void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
        {
            GLint location = glGetUniformLocation(m_RendererID, name.c_str());
            if(location == -1)
            {
                VM_CORE_CRITICAL("Uniform location {0} not found!", name);
                return;
            }
            glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
        }

        void OpenGLShader::UploadUniformInt(const std::string& name, const int& value)
        {
            GLint location = glGetUniformLocation(m_RendererID, name.c_str());
            if(location == -1)
            {
                VM_CORE_CRITICAL("Uniform location {0} not found!", name);
            }
            glUniform1i(location, value);
        }
        void OpenGLShader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count)
        {
            GLint location = glGetUniformLocation(m_RendererID, name.c_str());
            if(location == -1)
            {
                VM_CORE_CRITICAL("Uniform location {0} not found!", name);
            }
            glUniform1iv(location, count, values);
        }

    } // namespace Render
    
} // namespace VersaMachina
