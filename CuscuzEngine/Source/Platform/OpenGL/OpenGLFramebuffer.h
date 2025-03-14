#pragma once

#include "Cuscuz/Render/Framebuffer.h"

namespace Cuscuz
{
    class OpenGLFramebuffer : public Framebuffer
    {
        FramebufferSpecification m_Spec;
        uint32_t m_RendererID = 0;
        uint32_t m_ColorAttachment = 0;
        uint32_t m_DepthAttachment = 0;
        
    public:
        OpenGLFramebuffer(const FramebufferSpecification& spec);
        ~OpenGLFramebuffer() override;

        void Invalidate();

        void Bind() override;
        void Unbind() override;
        
        void Resize(uint32_t width, uint32_t height) override;
        
        const FramebufferSpecification& GetSpecification() const override { return m_Spec; }
        uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
    };
}
