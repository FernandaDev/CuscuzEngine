#pragma once
#include "Cuscuz/Core/Core.h"

namespace Cuscuz
{
    enum class FramebufferTextureFormat
    {
        None = 0,

        //Color
        RGBA8,
        RGBA16F,

        // Depth/Stencil
        DEPTH24STENCIL8,

        // Defaults
        Depth = DEPTH24STENCIL8,
    };

    struct FramebufferTextureConfig
    {
        FramebufferTextureFormat format = FramebufferTextureFormat::None;
        //TODO filtering/wrap

        FramebufferTextureConfig() = default;
        FramebufferTextureConfig(FramebufferTextureFormat format)
            : format(format) {}
    };

    struct FramebufferAttachments
    {
        std::vector<FramebufferTextureConfig> TextureConfigs;

        FramebufferAttachments() = default;
        FramebufferAttachments(const std::initializer_list<FramebufferTextureConfig>& textureConfigs)
            : TextureConfigs(textureConfigs) {}
        FramebufferAttachments(FramebufferAttachments&&) = default;
        FramebufferAttachments& operator=(FramebufferAttachments&&) = default;
    };
    
    struct FramebufferSpecification
    {
        uint32_t Width, Height = 0;
        uint32_t Samples = 1;
        FramebufferAttachments Attachments;

        bool SwapChainTarget = false;
    };
    
    class Framebuffer
    {
    public:
        virtual ~Framebuffer() = default;
        
        static CC_AssetRef<Framebuffer> Create(FramebufferSpecification&& spec);

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void Resize(uint32_t width, uint32_t height) = 0;
        
        virtual const FramebufferSpecification& GetSpecification() const = 0;
        virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0;
    };
}
