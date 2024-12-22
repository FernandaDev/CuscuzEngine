#include "pch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "RendererAPI.h"
#include "Core/CC_Core.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

CC_AssetRef<VertexBuffer> VertexBuffer::Create(const void* data, uint32_t size)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::OpenGL:
        return std::make_shared<OpenGLVertexBuffer>(data, size);
    case RendererAPI::API::None:
        {
            CC_ASSERT(false, "RendererAPI::None is not valid!")
            return nullptr;
        }    
    }

    CC_ASSERT(false, "Unknown Renderer API!")
    return nullptr;
}

CC_AssetRef<IndexBuffer> IndexBuffer::Create(const uint32_t* data, uint32_t count)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::OpenGL:
        return std::make_shared<OpenGLIndexBuffer>(data, count);
    case RendererAPI::API::None:
        {
            CC_ASSERT(false, "RendererAPI::None is not valid!")
            return nullptr;
        }    
    }

    CC_ASSERT(false, "Unknown Renderer API!")
    return nullptr;
}
