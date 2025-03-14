#pragma once
#include "Cuscuz/Core/Core.h"

namespace Cuscuz
{
    struct FramebufferSpecification
    {
        uint32_t Width, Height;
        uint32_t Samples = 1;

        bool SwapChainTarget = false;
    };
    
    class Framebuffer
    {
    public:
        virtual ~Framebuffer() = default;
        
        static CC_AssetRef<Framebuffer> Create(const FramebufferSpecification& spec);

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void Resize(uint32_t width, uint32_t height) = 0;
        
        virtual const FramebufferSpecification& GetSpecification() const = 0;
        virtual uint32_t GetColorAttachmentRendererID() const = 0;
    };
}
