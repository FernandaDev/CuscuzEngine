#include "pch.h"
#include "OpenGLShader.h"
#include "GL/glew.h"
#include "gtc/type_ptr.hpp"

namespace ShaderHelper
{
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
            if (line.find("#type") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                    type = ShaderType::VERTEX;
                else if (line.find("fragment") != std::string::npos)
                    type = ShaderType::FRAGMENT;
            }
            else
            {
                ss[static_cast<int>(type)] << line << '\n';
            }
        }

        return {
            ss[static_cast<int>(ShaderType::VERTEX)].str(),
            ss[static_cast<int>(ShaderType::FRAGMENT)].str()
        };
    }

    static std::string ExtractNameFromFile(const std::string& source)
    {
        //Example:
        //  "Assets/Shaders/Sprite.glsl"

        size_t nameBegin = source.find_last_of("/\\"); // try to find the last slash or backslash.

        if(nameBegin == std::string::npos) 
            nameBegin = 0; // we didn't find slashes, so we'll start at the beginning of the string.
        else
            nameBegin = nameBegin + 1; // we found a slash and the name starts 1 char after the slash.

        const size_t lastDot = source.rfind('.'); // try to find a dot/file extension.
        size_t nameCharCount;
    
        if(lastDot == std::string::npos) 
            nameCharCount = source.size() - nameBegin; // if we didn't find a dot, just count from the end of the source.
        else
            nameCharCount = lastDot - nameBegin; // otherwise count from the dot that we found.

        return source.substr(nameBegin, nameCharCount);
    }
}

OpenGLShader::OpenGLShader(const std::string& shaderFile)
{
    if(!PreProcess(shaderFile))
        return;
    
    m_Name = ShaderHelper::ExtractNameFromFile(shaderFile);
}

OpenGLShader::OpenGLShader(const std::string& name, const std::string& shaderFile)
{
    if(!PreProcess(shaderFile))
        return;

    m_Name = name;
}

OpenGLShader::~OpenGLShader()
{
    glDeleteProgram(m_RendererID);
    glDeleteShader(m_VertexShader);
    glDeleteShader(m_FragmentShader);
}

bool OpenGLShader::PreProcess(const std::string& shaderFile)
{
    const auto shaderSource = ShaderHelper::ParseShader(shaderFile);

    if (!CompileShader(shaderSource.VertexSource, GL_VERTEX_SHADER, m_VertexShader) ||
        !CompileShader(shaderSource.FragmentSource, GL_FRAGMENT_SHADER, m_FragmentShader))
    {
        return false;
    }

    m_RendererID = glCreateProgram();
    glAttachShader(m_RendererID, m_VertexShader);
    glAttachShader(m_RendererID, m_FragmentShader);
    glLinkProgram(m_RendererID);

    if (!IsValidProgram())
        return false;

    glDetachShader(m_RendererID, m_VertexShader);
    glDetachShader(m_RendererID, m_FragmentShader);

    return true;
}

bool OpenGLShader::CompileShader(const std::string& shaderSource, uint32_t shaderType, uint32_t& outShader)
{
    const char* contentsChar = shaderSource.c_str();

    outShader = glCreateShader(shaderType);
    glShaderSource(outShader, 1, &(contentsChar), nullptr);
    glCompileShader(outShader);

    if (!IsCompiled(outShader))
    {
        LOG_ERROR("Failed to compile shader: {0}", shaderType);
        return false;
    }

    return true;
}

bool OpenGLShader::IsCompiled(uint32_t shader)
{
    GLint status;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status != GL_TRUE)
    {
        char buffer[512] = {};
        glGetShaderInfoLog(shader, 511, nullptr, buffer);
        LOG_ERROR("GLSL Compile Failed: {0}", buffer);

        return false;
    }

    return true;
}


bool OpenGLShader::IsValidProgram() const
{
    GLint status;

    glGetProgramiv(m_RendererID, GL_LINK_STATUS, &status);

    if (status != GL_TRUE)
    {
        char buffer[512] = {};
        glGetProgramInfoLog(m_RendererID, 511, nullptr, buffer);
        LOG_ERROR("Program is not valid: {0}", buffer);

        return false;
    }

    return true;
}

void OpenGLShader::Bind() const
{
    glUseProgram(m_RendererID);
}

void OpenGLShader::Unbind() const
{
    glUseProgram(0);
}

void OpenGLShader::SetUniformF1(const char* name, float value)
{
    const auto uniformId = GetUniformID(name);

    glUniform1f(uniformId, value);
}

void OpenGLShader::SetUniformF2(const char* name, const glm::vec2& value)
{
    const auto uniformId = GetUniformID(name);

    glUniform2f(uniformId, value.x, value.y);
}

void OpenGLShader::SetUniformF3(const char* name, const glm::vec3& value)
{
    const auto uniformId = GetUniformID(name);

    glUniform3f(uniformId, value.x, value.y, value.z);
}

void OpenGLShader::SetUniformF4(const char* name, const glm::vec4& value)
{
    const auto uniformId = GetUniformID(name);

    glUniform4f(uniformId, value.x, value.y, value.z, value.w);
}

void OpenGLShader::SetUniformI(const char* name, int value)
{
    const auto uniformId = GetUniformID(name);

    glUniform1i(uniformId, value);
}

void OpenGLShader::SetUniformM4(const char* name, const glm::mat4x4& matrix)
{
    const auto uniformId = GetUniformID(name);

    glUniformMatrix4fv(uniformId, 1, GL_FALSE, glm::value_ptr(matrix));
}


int OpenGLShader::GetUniformID(const char* name)
{
    if (m_uniformMap.contains(name))
    {
        return m_uniformMap[name];
    }

    const auto uniformID = glGetUniformLocation(m_RendererID, name);
    if (uniformID == -1)
    {
        LOG_ERROR("Warning: uniform '{0}' doesn't exist or is unused!", name);
    }

    m_uniformMap[name] = uniformID;
    return uniformID;
}
