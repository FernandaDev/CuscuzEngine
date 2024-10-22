#pragma once

#include <string>
#include "GL/glew.h"

class Shader
{
    GLuint m_VertexShader;
    GLuint m_FragmentShader;
    GLuint m_ShaderProgram;
    
public:
    Shader() = default;
    ~Shader() = default;

    bool Load(const std::string& vertName, const std::string& fragName);
    void Unload() const;
    
    void SetActive() const;

private:
    bool CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader);
    bool IsCompiled(GLuint shader);
    bool IsValidProgram() const;
    
};
