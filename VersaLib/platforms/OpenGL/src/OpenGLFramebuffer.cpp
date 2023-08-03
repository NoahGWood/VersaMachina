#include "pch.h"
#include "OpenGL/include/OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace VersaMachina
{
    namespace Render
    {
        OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec)
            : m_Specification(spec)
        {
            Invalidate();
        }

        OpenGLFramebuffer::~OpenGLFramebuffer()
        {
            glDeleteFramebuffers(1, &m_RendererID);
            glDeleteTextures(1, &m_ColorAttachment);
            glDeleteTextures(1, &m_DepthAttachment);
        }

        void OpenGLFramebuffer::Invalidate()
        {
            if(m_RendererID)
            {
                glDeleteFramebuffers(1, &m_RendererID);
                glDeleteTextures(1, &m_ColorAttachment);
                glDeleteTextures(1, &m_DepthAttachment);
            }
            // Create frame buffer
            glCreateFramebuffers(1, &m_RendererID);
            glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

            // Create color texture buffer
            glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
            // Bind color texture
            glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
            // Set texture parameters
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.Width, m_Specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // Bind texture to framebuffer
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

            // Create depth texture buffer
            glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
            // Bind texture
            glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
            // Set properties
            glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height);
//            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);

            // Final check
    		VM_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");
            // Bind framebuffer
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }


        void OpenGLFramebuffer::Bind()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
            glViewport(0,0,m_Specification.Width, m_Specification.Height);
        }
        void OpenGLFramebuffer::Unbind()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
        {
            m_Specification.Width = width;
            m_Specification.Height = height;
            Invalidate();
        }

    } // namespace Render
    
} // namespace VersaMachina
