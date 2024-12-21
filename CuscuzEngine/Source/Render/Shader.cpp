#include "pch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

Shader* Shader::Create(const std::string& shaderFile)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::OpenGL :
        return new OpenGLShader(shaderFile);
    case RendererAPI::API::None:
        CC_ASSERT(false, "Unknown renderer API!")
    }

    CC_ASSERT(false, "Unknown renderer API!")
    return nullptr;
}
