#include "pch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

CC_AssetRef<VertexArray> VertexArray::Create()
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::OpenGL:
        return CreateAssetRef<OpenGLVertexArray>();
    case RendererAPI::API::None:
        {
            CC_ASSERT(false, "RendererAPI::None is not valid!")
            return nullptr;
        }    
    }

    CC_ASSERT(false, "Unknown Renderer API!")
    return nullptr;
}
