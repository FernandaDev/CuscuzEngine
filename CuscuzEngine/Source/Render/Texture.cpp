#include "pch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"

CC_AssetRef<Texture2D> Texture2D::Create(std::string&& filepath)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::OpenGL:
        return std::make_shared<OpenGLTexture2D>(std::move(filepath));
    case RendererAPI::API::None:
        {
            CC_ASSERT(false, "RendererAPI::None is not valid!")
            return nullptr;
        }    
    }

    CC_ASSERT(false, "Unknown Renderer API!")
    return nullptr;
}
