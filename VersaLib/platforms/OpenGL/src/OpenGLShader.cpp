#include "pch.h"
#include "OpenGL/include/OpenGLShader.h"
#include "glad/glad.h"
#include <glm/gtc/type_ptr.hpp>

#include <shaderc/shaderc.hpp>
#include <spirv_cross.hpp>
#include <spirv_glsl.hpp>

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

        static shaderc_shader_kind GLShaderStageToShaderC(GLenum stage)
        {
            switch(stage)
            {
                case GL_VERTEX_SHADER: return shaderc_glsl_vertex_shader;
				case GL_FRAGMENT_SHADER: return shaderc_glsl_fragment_shader;
			}
			VM_CORE_ASSERT(false);
			return (shaderc_shader_kind)0;
        }
        
        static const char* GLShaderStageToString(GLenum stage)
        {
            switch(stage)
            {
                case GL_VERTEX_SHADER: return "GL_VERTEX_SHADER";
                case GL_FRAGMENT_SHADER: return "GL_FRAGMENT_SHADER";
            }
            VM_CORE_ASSERT(false);
            return nullptr;
        }

        static const char* GetCacheDirectory()
        {
            // TODO: Make suer the assets dir is valid
            return "/tmp/assets/cache/shader/opengl";
        }

        static void CreateCacheDirectoryIfNeeded()
        {
            std::string cacheDir = GetCacheDirectory();
            if(!std::filesystem::exists(cacheDir))
                std::filesystem::create_directories(cacheDir);
        }

        static const char* GLShaderStageCachedOpenGLFileExtension(uint32_t stage)
        {
            switch(stage)
            {
                case GL_VERTEX_SHADER: return ".cached_opengl.vert";
                case GL_FRAGMENT_SHADER: return ".cached_opengl.frag";
            }
            VM_CORE_ASSERT(false);
            return "";
        }

        static const char* GLShaderStageCachedVulkanFileExtension(uint32_t stage)
        {
            switch(stage)
            {
                case GL_VERTEX_SHADER: return ".cached_vulkan.vert";
                case GL_FRAGMENT_SHADER: return ".cached_vulkan.frag";
            }
            VM_CORE_ASSERT(false);
            return "";
        }

        OpenGLShader::OpenGLShader(const std::string& filepath)
            : m_FilePath(filepath)
        {
            VM_PROFILE_FUNCTION();                
            CreateCacheDirectoryIfNeeded();
            std::string source = ReadFile(filepath);
            auto shaderSources = PreProcess(source);
            //Compile(shaderSources);
            CompileOrGetVulkanBinaries(shaderSources);
            CompileOrGetOpenGLBinaries();
            CreateProgram();

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

    		CompileOrGetVulkanBinaries(sources);
    		CompileOrGetOpenGLBinaries();
    		CreateProgram();
        }
        
        OpenGLShader::~OpenGLShader()
        {
            VM_PROFILE_FUNCTION();                

            glDeleteProgram(m_RendererID);
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


        void OpenGLShader::CompileOrGetVulkanBinaries(const std::unordered_map<GLenum, std::string>& shaderSources)
        {
            GLuint program = glCreateProgram();
            
            shaderc::Compiler compiler;
            shaderc::CompileOptions options;
            options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2);
            const bool optimize = true;
            if(optimize)
                options.SetOptimizationLevel(shaderc_optimization_level_performance);
            
            std::filesystem::path cacheDir = GetCacheDirectory();

            auto& shaderData = m_VulkanSPIRV;
            shaderData.clear();
            for(auto&& [stage,source] : shaderSources)
            {
                std::filesystem::path shaderFilePath = m_FilePath;
                std::filesystem::path cachedPath = cachedPath / (shaderFilePath.filename().string() + GLShaderStageCachedVulkanFileExtension(stage));

                std::ifstream in(cachedPath, std::ios::in | std::ios::binary);
                if(in.is_open())
                {
                    in.seekg(0, std::ios::end);
                    auto size = in.tellg();
                    in.seekg(0, std::ios::beg);

                    auto& data = shaderData[stage];
                    data.resize(size/sizeof(uint32_t));
                    in.read((char*)data.data(), size);
                } else {
    				shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source, GLShaderStageToShaderC(stage), m_FilePath.c_str(), options);
    				if (module.GetCompilationStatus() != shaderc_compilation_status_success)
    				{
    					VM_CORE_ERROR(module.GetErrorMessage());
    					VM_CORE_ASSERT(false);
    				}

    				shaderData[stage] = std::vector<uint32_t>(module.cbegin(), module.cend());

    				std::ofstream out(cachedPath, std::ios::out | std::ios::binary);
    				if (out.is_open())
    				{
    					auto& data = shaderData[stage];
    					out.write((char*)data.data(), data.size() * sizeof(uint32_t));
    					out.flush();
    					out.close();
    				}
                }
            }
            for(auto&& [stage, data] : shaderData)
                Reflect(stage, data);
        }
        void OpenGLShader::CompileOrGetOpenGLBinaries()
        {
            auto& shaderData = m_OpenGLSPIRV;

            shaderc::Compiler compiler;
            shaderc::CompileOptions options;
            options.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);
            const bool optimize = false;
            if(optimize)
                options.SetOptimizationLevel(shaderc_optimization_level_performance);

            std::filesystem::path cacheDir = GetCacheDirectory();

            shaderData.clear();
            m_OpenGLSourceCode.clear();
            
    		for (auto&& [stage, spirv] : m_VulkanSPIRV)
    		{
    			std::filesystem::path shaderFilePath = m_FilePath;
    			std::filesystem::path cachedPath = cacheDir / (shaderFilePath.filename().string() + GLShaderStageCachedOpenGLFileExtension(stage));

    			std::ifstream in(cachedPath, std::ios::in | std::ios::binary);
    			if (in.is_open())
    			{
    				in.seekg(0, std::ios::end);
    				auto size = in.tellg();
    				in.seekg(0, std::ios::beg);

    				auto& data = shaderData[stage];
    				data.resize(size / sizeof(uint32_t));
    				in.read((char*)data.data(), size);
    			}
    			else
    			{
    				spirv_cross::CompilerGLSL glslCompiler(spirv);
    				m_OpenGLSourceCode[stage] = glslCompiler.compile();
    				auto& source = m_OpenGLSourceCode[stage];

    				shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source, GLShaderStageToShaderC(stage), m_FilePath.c_str());
    				if (module.GetCompilationStatus() != shaderc_compilation_status_success)
    				{
    					VM_CORE_ERROR(module.GetErrorMessage());
    					VM_CORE_ASSERT(false);
    				}

    				shaderData[stage] = std::vector<uint32_t>(module.cbegin(), module.cend());

		    		std::ofstream out(cachedPath, std::ios::out | std::ios::binary);
		    		if (out.is_open())
		    		{
		    			auto& data = shaderData[stage];
		    			out.write((char*)data.data(), data.size() * sizeof(uint32_t));
		    			out.flush();
		    			out.close();
		    		}
		    	}
		    }
        }
        void OpenGLShader::CreateProgram()
        {
            GLuint program = glCreateProgram();
            std::vector<GLuint> shaderIDs;
            for(auto&& [stage, spirv] : m_OpenGLSPIRV)
            {
                GLuint shaderID = shaderIDs.emplace_back(glCreateShader(stage));
                glShaderBinary(1, &shaderID, GL_SHADER_BINARY_FORMAT_SPIR_V, spirv.data(), spirv.size() * sizeof(uint32_t));
                glSpecializeShader(shaderID, "main", 0, nullptr, nullptr);
                glAttachShader(program, shaderID);
            }
            glLinkProgram(program);

            GLint isLinked;
            glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
    		if (isLinked == GL_FALSE)
    		{
    			GLint maxLength;
    			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

    			std::vector<GLchar> infoLog(maxLength);
    			glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data());
    			VM_CORE_ERROR("Shader linking failed ({0}):\n{1}", m_FilePath, infoLog.data());

    			glDeleteProgram(program);

    			for (auto id : shaderIDs)
    				glDeleteShader(id);
    		}

    		for (auto id : shaderIDs)
    		{
    			glDetachShader(program, id);
    			glDeleteShader(id);
    		}

    		m_RendererID = program;            
        }
        void OpenGLShader::Reflect(GLenum stage, const std::vector<uint32_t>& shaderData)
        {
            spirv_cross::Compiler compiler(shaderData);
            spirv_cross::ShaderResources resources = compiler.get_shader_resources();

            VM_CORE_TRACE("OpenGLShader::Reflect - {0} {1}", GLShaderStageToString(stage), m_FilePath);
            VM_CORE_TRACE("    {0} uniform buffers", resources.uniform_buffers.size());
            VM_CORE_TRACE("    {0} resources", resources.sampled_images.size());

            VM_CORE_TRACE("Uniform buffers:");
            for (const auto& resource : resources.uniform_buffers)
            {
                const auto& bufferType = compiler.get_type(resource.base_type_id);
                uint32_t bufferSize = compiler.get_declared_struct_size(bufferType);
                uint32_t binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
                int memberCount = bufferType.member_types.size();

                VM_CORE_TRACE("  {0}", resource.name);
                VM_CORE_TRACE("    Size = {0}", bufferSize);
                VM_CORE_TRACE("    Binding = {0}", binding);
                VM_CORE_TRACE("    Members = {0}", memberCount);
            }
        }

    } // namespace Render
    
} // namespace VersaMachina
