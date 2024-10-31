#pragma once

#include <string>

#include "fwd.hpp"

class Shader
{
    unsigned int m_VertexShader;
    unsigned int m_FragmentShader;
    unsigned int m_ShaderProgram;

    std::unordered_map<std::string, unsigned int> m_uniformMap;
    
public:
    Shader() = default;
    ~Shader() = default;

    bool Load(const std::string& shaderFile);
    void Unload() const;
    
    void SetActive() const;
    void SetMatrixUniform(const char* name, const glm::mat4x4& matrix);

private:
    bool CompileShader(const std::string& fileName, unsigned int shaderType, unsigned int& outShader);
    bool IsCompiled(unsigned int shader);
    bool IsValidProgram() const;
    unsigned int GetUniformID(const char* name);  
};
