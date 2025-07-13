#include "pch.h"
#include "OpenGLFramebuffer.h"

#include "GLUtils.h"
#include "GL/glew.h"

namespace Cuscuz
{
    OpenGLFramebuffer::OpenGLFramebuffer(FramebufferSpecification&& spec):
        m_Spec(std::move(spec))
    {
        for(const auto& config : m_Spec.Attachments.TextureConfigs)
        {
            if(!GLUtils::IsDepthFormat(config.format))
                m_ColorAttachmentsConfig.emplace_back(config);
            else
                m_DepthAttachmentConfig = config;
        }
        
        Invalidate();
    }

    OpenGLFramebuffer::~OpenGLFramebuffer() { ClearBuffers(); }

    void OpenGLFramebuffer::Invalidate()
    {
        if(m_RendererID)
            ClearBuffers();
        
        glCreateFramebuffers(1, &m_RendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

        if(!m_ColorAttachmentsConfig.empty())
        {
            m_ColorAttachments.resize(m_ColorAttachmentsConfig.size());
            GLUtils::CreateTextures(m_ColorAttachments.data(), m_ColorAttachmentsConfig.size());

            for (size_t i = 0; i < m_ColorAttachments.size(); ++i)
            {
                GLUtils::BindTexture(m_ColorAttachments[i]);

                const auto format = GLUtils::GetGLFormat(m_ColorAttachmentsConfig[i].format);
                GLUtils::AttachColorTexture(m_ColorAttachments[i], format, m_Spec.Width, m_Spec.Height, i);
            }
        }
        
        if(m_DepthAttachmentConfig.format != FramebufferTextureFormat::None)
        {
            GLUtils::CreateTextures(&m_DepthAttachment, 1);
            GLUtils::BindTexture(m_DepthAttachment);

            const auto depthFormat = GLUtils::GetGLFormat(m_DepthAttachmentConfig.format);
            GLUtils::AttachDepthTexture(m_DepthAttachment, depthFormat, GL_DEPTH_STENCIL_ATTACHMENT, m_Spec.Width, m_Spec.Height);
        }
        else
            m_DepthAttachment = 0;
        
        if(m_ColorAttachments.size() > 1)
        {
            CC_ASSERT(m_ColorAttachments.size() <= 4, "There should only be 4 buffers!")
            constexpr GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
            glDrawBuffers(static_cast<GLsizei>(m_ColorAttachments.size()), buffers);
        }
        else if(m_ColorAttachments.empty())
            glDrawBuffer(GL_NONE);

        CC_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!")
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        glViewport(0,0, m_Spec.Width, m_Spec.Height);
    }

    void OpenGLFramebuffer::Unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
    {
        m_Spec.Width = width;
        m_Spec.Height = height;

        Invalidate();
    }

    void OpenGLFramebuffer::ClearBuffers()
    {
        glDeleteFramebuffers(1, &m_RendererID);
        glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
        glDeleteTextures(1, &m_DepthAttachment);

        m_ColorAttachments.clear();
        m_DepthAttachment = 0;
    }
}
