#include "pch.h"
#include "Render/Renderer.h"
#include "Render/Shader.h"
#include "OpenGL/include/OpenGLShader.h"

namespace VersaMachina
{
    namespace Render
    {

        void ShaderLibrary::Add(const Ref<Shader>& shader)
        {
            std::string& n = (std::string&)shader->GetName();
            std::string& name = n;
            int x = 1;
            while(true)
            {
                if(Exists(name))
                {
                    VM_CORE_WARN("Shader {0} already exists. Retrying as {1}_{2}", name, name, x);
                    x++;
                    name = n + "_" + std::to_string(x);
                }
                else 
                {
                    break;
                }
            }
            VM_CORE_INFO("Adding shader: {0}", name);
            m_Shaders[name] = shader;
        }
        Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
        {
            auto shader = Shader::Create(filepath);
            Add(shader);
            return shader;
        }
        Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
        {
            auto shader = Shader::Create(filepath);
            Add(shader);
            shader->SetName(name);
            return shader;
        }
        Ref<Shader> ShaderLibrary::Get(const std::string& name)
        {
            VM_CORE_ASSERT(Exists(name), "Shader not found!");
            return m_Shaders[name];
        }

        bool ShaderLibrary::Exists(const std::string& name) const
        {
            return m_Shaders.find(name) != m_Shaders.end();
        }

    } // namespace Render
    
} // namespace VersaMachina

