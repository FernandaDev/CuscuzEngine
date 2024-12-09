#include "pch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

VertexArray* VertexArray::Create()
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::OpenGL:
        return new OpenGLVertexArray();
    case RendererAPI::None:
        {
            CC_ASSERT(false, "RendererAPI::None is not valid!")
            return nullptr;
        }    
    }

    CC_ASSERT(false, "Unknown Renderer API!")
    return nullptr;
}
