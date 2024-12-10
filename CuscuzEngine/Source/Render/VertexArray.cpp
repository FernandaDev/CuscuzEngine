#include "pch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

VertexArray* VertexArray::Create()
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::OpenGL:
        return new OpenGLVertexArray();
    case RendererAPI::API::None:
        {
            CC_ASSERT(false, "RendererAPI::None is not valid!")
            return nullptr;
        }    
    }

    CC_ASSERT(false, "Unknown Renderer API!")
    return nullptr;
}
