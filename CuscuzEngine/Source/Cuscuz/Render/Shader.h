#pragma once

#include <string>
#include <unordered_map>
#include "fwd.hpp"
#include "..\Core\Core.h"

namespace Cuscuz
{
    class Shader
    {
    protected:
        std::unordered_map<std::string, int> m_uniformMap;

    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual const std::string& GetName() const = 0;

        virtual void SetFloat(const char* name, float value) = 0;
        virtual void SetFloat2(const char* name, const glm::vec2& value) = 0;
        virtual void SetFloat3(const char* name, const glm::vec3& value) = 0;
        virtual void SetFloat4(const char* name, const glm::vec4& value) = 0;
        virtual void SetInt(const char* name, int32_t value) = 0;
        virtual void SetIntArray(const char* name, int* values, int32_t count) = 0;
        virtual void SetMatrix4(const char* name, const glm::mat4x4& matrix) = 0;

        static CC_AssetRef<Shader> Create(const std::string& shaderFile);
        static CC_AssetRef<Shader> Create(const std::string& name, const std::string& shaderFile);
    };

    class ShaderLibrary
    {
        std::unordered_map<std::string, CC_AssetRef<Shader>> m_Shaders;

    public:
        ShaderLibrary();

        void Add(const CC_AssetRef<Shader>& shader);
        void Add(const std::string& name, const CC_AssetRef<Shader>& shader);
        CC_AssetRef<Shader> Load(const std::string& filepath);
        CC_AssetRef<Shader> Load(const std::string& name, const std::string& filepath);

        CC_AssetRef<Shader> Get(const std::string& name);

    private:
        bool Exists(const std::string& name) const;
    };
}
