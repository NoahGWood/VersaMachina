# Shader

Shaders are implemented in VersaMachina as an abstract class allowing for platform-specific to be implemented.

## Render/Shader.h

```
#pragma once

#include <string>

namespace VersaMachina
{
    namespace Render
    {
        class Shader
        {
            public:
                Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
                ~Shader();

                void Bind() const;
                void UnBind() const;
                inline void* GetNativeShader() { return m_Shader; }

            private:
                uint32_t m_RendererID;
                void* m_Shader;

        };
    } // namespace Render
    
} // namespace VersaMachina
```
