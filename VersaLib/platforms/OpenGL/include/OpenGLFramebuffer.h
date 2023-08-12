#include "Render/Framebuffer.h"
#include <glm/glm.hpp>

namespace VersaMachina
{
    namespace Render
    {
        class OpenGLFramebuffer : public Framebuffer
        {
            public:
                OpenGLFramebuffer(const FramebufferSpecification& spec);
                virtual ~OpenGLFramebuffer() override;


                virtual void Bind() override;
                virtual void Unbind() override;

                virtual void Resize(uint32_t width, uint32_t height) override;
                virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) override;

                virtual void ClearAttachmentInt(uint32_t index, int value) override;

                virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override { VM_CORE_ASSERT(index<m_ColorAttachments.size()); return m_ColorAttachments[index]; };
        		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }
        
                void Invalidate();
        
            private:
                uint32_t m_RendererID = 0;
                uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
                FramebufferSpecification m_Specification;

                std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecs;
                FramebufferTextureSpecification m_DepthAttachmentSpec;

                std::vector<uint32_t> m_ColorAttachments;
        };

    } // namespace Render
    
} // namespace VersaMachina
