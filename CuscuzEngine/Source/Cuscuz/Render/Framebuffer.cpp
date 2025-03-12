#include "pch.h"

#include "Framebuffer.h"
#include "Renderer.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Cuscuz
{
    CC_AssetRef<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::OpenGL:
            return CreateAssetRef<OpenGLFramebuffer>(spec);
        case RendererAPI::API::None:
            {
                CC_ASSERT(false, "RendererAPI::None is not valid!")
                return nullptr;
            }    
        }

        CC_ASSERT(false, "Unknown Renderer API!")
        return nullptr;
    }
}
