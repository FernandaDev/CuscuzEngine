#pragma once

#include <string>
#include "Render/Shader.h"

class OpenGLShader : public Shader
{
    uint32_t m_VertexShader;
    uint32_t m_FragmentShader;
    uint32_t m_RendererID;
    std::string m_Name;
    
public:
    OpenGLShader(const std::string& shaderFile);
    OpenGLShader(const std::string& name, const std::string& shaderFile);
    ~OpenGLShader() override;

    void Bind() const override;
    void Unbind() const override;

    const std::string& GetName() const override { return m_Name; }

    void SetUniformF1(const char* name, float value) override;
    void SetUniformF2(const char* name, const glm::vec2& value) override;
    void SetUniformF3(const char* name, const glm::vec3& value) override;
    void SetUniformF4(const char* name, const glm::vec4& value) override;
    void SetUniformI(const char* name, int value) override;
    void SetUniformM4(const char* name, const glm::mat4x4& matrix) override;
    
private:
    bool PreProcess(const std::string& shaderFile);
    bool CompileShader(const std::string& shaderSource, uint32_t shaderType, uint32_t& outShader);
    bool IsCompiled(uint32_t shader);
    bool IsValidProgram() const;
    int GetUniformID(const char* name);  
};
