#include "pch.h"
#include "Shader.h"

bool Shader::Load(const std::string& vertName, const std::string& fragName)
{
    if(!CompileShader(vertName, GL_VERTEX_SHADER, m_VertexShader) ||
        !CompileShader(fragName, GL_FRAGMENT_SHADER, m_FragmentShader))
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

bool Shader::CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader)
{
    const std::ifstream shaderFile(fileName);

    if(shaderFile.is_open())
    {
        std::stringstream ss;
        ss << shaderFile.rdbuf();
        const std::string contents = ss.str();
        const char* contentsChar = contents.c_str();

        outShader = glCreateShader(shaderType);
        glShaderSource(outShader, 1, &(contentsChar), nullptr);
        glCompileShader(outShader);

        if(!IsCompiled(outShader))
        {
            LOG_ERROR("Failed to compile shader: {0}", fileName.c_str());
            return false;
        }        
    }
    else
    {
        LOG_ERROR("Shader file not found: {0}", fileName);
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
