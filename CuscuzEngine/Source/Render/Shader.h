#pragma once

#include <string>

class Shader
{
    unsigned int m_VertexShader;
    unsigned int m_FragmentShader;
    unsigned int m_ShaderProgram;
    
public:
    Shader() = default;
    ~Shader() = default;

    bool Load(const std::string& shaderFile);
    void Unload() const;
    
    void SetActive() const;

private:
    bool CompileShader(const std::string& fileName, unsigned int shaderType, unsigned int& outShader);
    bool IsCompiled(unsigned int shader);
    bool IsValidProgram() const;
    
};
