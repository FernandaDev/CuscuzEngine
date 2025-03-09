#include "pch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"

namespace Cuscuz
{
    CC_AssetRef<Texture2D> Texture2D::Create(std::string&& filepath)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::OpenGL:
            return CreateAssetRef<OpenGLTexture2D>(std::move(filepath));
        case RendererAPI::API::None:
            {
                CC_ASSERT(false, "RendererAPI::None is not valid!")
                return nullptr;
            }    
        }

        CC_ASSERT(false, "Unknown Renderer API!")
        return nullptr;
    }

    CC_AssetRef<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::OpenGL:
            return CreateAssetRef<OpenGLTexture2D>(width, height);
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