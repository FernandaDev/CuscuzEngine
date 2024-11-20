#pragma once

#include <string>

#include "fwd.hpp"

class Shader
{
    unsigned int m_VertexShader;
    unsigned int m_FragmentShader;
    unsigned int m_ShaderProgram;

    std::unordered_map<std::string, int> m_uniformMap;
    
public:
    Shader() = default;
    ~Shader() = default;

    bool Load(const std::string& shaderFile);
    void Unload() const;
    
    void SetActive() const;
    void SetUniformF1(const char* name, float value);
    void SetUniformF2(const char* name, const glm::vec2& value);
    void SetUniformF3(const char* name, const glm::vec3& value);
    void SetUniformF4(const char* name, const glm::vec4& value);
    void SetUniformI(const char* name, int value);
    void SetUniformM4(const char* name, const glm::mat4x4& matrix);

private:
    bool CompileShader(const std::string& fileName, unsigned int shaderType, unsigned int& outShader);
    bool IsCompiled(unsigned int shader);
    bool IsValidProgram() const;
    int GetUniformID(const char* name);  
};
