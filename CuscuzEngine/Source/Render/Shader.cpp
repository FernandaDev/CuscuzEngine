#include "pch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

CC_AssetRef<Shader> Shader::Create(const std::string& shaderFile)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::OpenGL :
        return CreateAssetRef<OpenGLShader>(shaderFile);
    case RendererAPI::API::None:
        CC_ASSERT(false, "Unknown renderer API!")
    }

    CC_ASSERT(false, "Unknown renderer API!")
    return nullptr;
}

CC_AssetRef<Shader> Shader::Create(const std::string& name, const std::string& shaderFile)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::OpenGL :
        return CreateAssetRef<OpenGLShader>(name, shaderFile);
    case RendererAPI::API::None:
        CC_ASSERT(false, "Unknown renderer API!")
    }

    CC_ASSERT(false, "Unknown renderer API!")
    return nullptr;
}

ShaderLibrary::ShaderLibrary()
{
    Load("Sprite", "Assets/Shaders/Sprite.glsl");
}

void ShaderLibrary::Add(const CC_AssetRef<Shader>& shader)
{
    auto& name = shader->GetName();
    Add(name, shader);
}

void ShaderLibrary::Add(const std::string& name, const CC_AssetRef<Shader>& shader)
{
    CC_ASSERT(!Exists(name), "Shader already exists!")
    m_Shaders[name] = shader;
}

CC_AssetRef<Shader> ShaderLibrary::Load(const std::string& filepath)
{
    auto shader = Shader::Create(filepath);
    Add(shader);
    return shader;
}

CC_AssetRef<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
{
    auto shader = Shader::Create(filepath);
    Add(name, shader);
    return shader;
}

CC_AssetRef<Shader> ShaderLibrary::Get(const std::string& name)
{
    CC_ASSERT(Exists(name), "Shader not found!")
    return m_Shaders[name];
}

bool ShaderLibrary::Exists(const std::string& name) const
{
    return m_Shaders.find(name) != m_Shaders.end();
}