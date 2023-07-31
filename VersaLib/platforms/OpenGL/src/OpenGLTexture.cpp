#include "pch.h"
#include "Render/Texture.h"
#include "Render/Renderer.h"

#include "OpenGL/include/OpenGLTexture.h"

#include "stb_image.h"

namespace VersaMachina
{
    namespace Render
    {
        OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
            : m_Width(width), m_Height(height), m_InternalFormat(GL_RGBA8), m_DataFormat(GL_RGBA)
        {        
            VM_PROFILE_FUNCTION();

            glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
            glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);
        

            glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        }


        OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
            : m_Path(path)
        {
            VM_PROFILE_FUNCTION();

            int width, height, channels;
            stbi_set_flip_vertically_on_load(1);
            stbi_uc* data = nullptr;
            {
                VM_PROFILE_SCOPE("stbi_load - OpenGLTexture2D::OpenGLTexture2D(const std::string& path)");
                data = stbi_load(m_Path.c_str(), &width, &height, &channels, 0);
            }

            VM_CORE_ASSERT(data, "Failed to load image file!");
            m_Width = width;
            m_Height = height;
            
            GLenum internalFormat = 0, dataFormat = 0;
            if(channels==4)
            {
                internalFormat = GL_RGBA8;
                dataFormat = GL_RGBA;
            } else if(channels==3){
                internalFormat = GL_RGB8;
                dataFormat = GL_RGB;
            }

            VM_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");
            
            m_InternalFormat = internalFormat;
            m_DataFormat = dataFormat;

            glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
            glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);
        

            glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

            glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

            stbi_image_free(data);
        }
        OpenGLTexture2D::~OpenGLTexture2D()
        {
            VM_PROFILE_FUNCTION();

            glDeleteTextures(1, &m_RendererID);
        }
        void OpenGLTexture2D::Bind(uint32_t slot) const
        {
            VM_PROFILE_FUNCTION();

            glBindTextureUnit(slot, m_RendererID);
        }

        void OpenGLTexture2D::SetData(void* data, uint32_t size)
        {
            VM_PROFILE_FUNCTION();

            uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
            VM_CORE_ASSERT(size == m_Width * m_Height * bpp, "Size of buffer is not the same size as texture!");

            glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
        }
    } // namespace Render
    
} // namespace VersaMachina
