#pragma once

#include "Cuscuz/Render/Framebuffer.h"

namespace Cuscuz
{
    class OpenGLFramebuffer : public Framebuffer
    {
        FramebufferSpecification m_Spec;
        uint32_t m_RendererID;
        uint32_t m_ColorAttachment;
        uint32_t m_DepthAttachment;
        
    public:
        OpenGLFramebuffer(const FramebufferSpecification& spec);
        ~OpenGLFramebuffer() override;

        void Invalidate();

        void Bind() override;
        void Unbind() override;
        
        const FramebufferSpecification& GetSpecification() const override { return m_Spec; }
        uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
    };
}
