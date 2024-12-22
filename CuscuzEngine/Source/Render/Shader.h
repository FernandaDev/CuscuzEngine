#pragma once

#include <string>
#include "fwd.hpp"
#include "Core/CC_Core.h"

class Shader
{
protected:
    std::unordered_map<std::string, int> m_uniformMap;
    
public:
    virtual ~Shader() = default;
    
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void SetUniformF1(const char* name, float value) = 0;
    virtual void SetUniformF2(const char* name, const glm::vec2& value) = 0;
    virtual void SetUniformF3(const char* name, const glm::vec3& value) = 0;
    virtual void SetUniformF4(const char* name, const glm::vec4& value) = 0;
    virtual void SetUniformI(const char* name, int value) = 0;
    virtual void SetUniformM4(const char* name, const glm::mat4x4& matrix) = 0;

    static CC_AssetRef<Shader> Create(const std::string& shaderFile);
};
