#pragma once

#include "Cuscuz/Render/Framebuffer.h"

namespace Cuscuz
{
    class OpenGLFramebuffer : public Framebuffer
    {
        FramebufferSpecification m_Spec;
        uint32_t m_RendererID = 0;

        std::vector<uint32_t> m_ColorAttachments;
        std::vector<FramebufferTextureConfig> m_ColorAttachmentsConfig;
        
        uint32_t m_DepthAttachment = 0;
        FramebufferTextureConfig m_DepthAttachmentConfig;
        
    public:
        OpenGLFramebuffer(FramebufferSpecification&& spec);
        ~OpenGLFramebuffer() override;

        void Invalidate();

        void Bind() override;
        void Unbind() override;
        
        void Resize(uint32_t width, uint32_t height) override;
        
        const FramebufferSpecification& GetSpecification() const override { return m_Spec; }
        uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override { return m_ColorAttachments[index]; }

    private:
        void ClearBuffers();
    };
}
