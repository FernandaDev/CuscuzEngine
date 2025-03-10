﻿#include "pch.h"

#include "Buffer.h"
#include "Renderer.h"
#include "RendererAPI.h"
#include <Cuscuz/Core/Core.h>
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Cuscuz
{
    CC_AssetRef<VertexBuffer> VertexBuffer::Create(uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::OpenGL:
            return CreateAssetRef<OpenGLVertexBuffer>(size);
        case RendererAPI::API::None:
            {
                CC_ASSERT(false, "RendererAPI::None is not valid!")
                return nullptr;
            }    
        }

        CC_ASSERT(false, "Unknown Renderer API!")
        return nullptr;
    }

    CC_AssetRef<VertexBuffer> VertexBuffer::Create(const void* data, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::OpenGL:
            return CreateAssetRef<OpenGLVertexBuffer>(data, size);
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
            return CreateAssetRef<OpenGLIndexBuffer>(data, count);
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