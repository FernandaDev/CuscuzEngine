#include "pch.h"
#include "Shader.h"
#include "GL/glew.h"

struct ShaderSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderSource ParseShader(const std::string& file)
{
    std::ifstream stream(file);

    enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (std::getline(stream, line))
    {
        if(line.find("#type") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[static_cast<int>(type)] << line << '\n';
        }
    }

    return { ss[static_cast<int>(ShaderType::VERTEX)].str(),
             ss[static_cast<int>(ShaderType::FRAGMENT)].str() };
}

bool Shader::Load(const std::string& shaderFile)
{
    const auto shaderSource = ParseShader(shaderFile);
    
    if(!CompileShader(shaderSource.VertexSource, GL_VERTEX_SHADER, m_VertexShader) ||
        !CompileShader(shaderSource.FragmentSource, GL_FRAGMENT_SHADER, m_FragmentShader))
    {
        return false;
    }

    m_ShaderProgram = glCreateProgram();
    glAttachShader(m_ShaderProgram, m_VertexShader);
    glAttachShader(m_ShaderProgram, m_FragmentShader);
    glLinkProgram(m_ShaderProgram);

    if(!IsValidProgram())
        return false;

    return true;
}

void Shader::Unload() const
{
    glDeleteProgram(m_ShaderProgram);
    glDeleteShader(m_VertexShader);
    glDeleteShader(m_FragmentShader);
}

void Shader::SetActive() const
{
    glUseProgram(m_ShaderProgram);
}

bool Shader::CompileShader(const std::string& shaderSource, GLenum shaderType, GLuint& outShader)
{
    const char* contentsChar = shaderSource.c_str();

    outShader = glCreateShader(shaderType);
    glShaderSource(outShader, 1, &(contentsChar), nullptr);
    glCompileShader(outShader);
    
    if(!IsCompiled(outShader))
    {
        LOG_ERROR("Failed to compile shader: {0}", shaderType);
        return false;
    }

    return true;
}

bool Shader::IsCompiled(GLuint shader)
{
    GLint status;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if(status != GL_TRUE)
    {
        char buffer[512] = {};
        glGetShaderInfoLog(shader, 511, nullptr, buffer);
        LOG_ERROR("GLSL Compile Failed: {0}", buffer);

        return false;
    }

    return true;
}

bool Shader::IsValidProgram() const
{
    GLint status;

    glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &status);

    if(status != GL_TRUE)
    {
        char buffer[512] = {};
        glGetProgramInfoLog(m_ShaderProgram, 511, nullptr, buffer);
        LOG_ERROR("Program is not valid: {0}", buffer);

        return false;
    }

    return true;
}
