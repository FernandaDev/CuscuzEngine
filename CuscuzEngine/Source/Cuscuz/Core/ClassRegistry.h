#pragma once

#include <functional>
#include <optional>
#include <Cuscuz/Utils/Log.h>

namespace Cuscuz
{
    struct ClassType
    {
        std::string Name;
        size_t Size;
        std::function<void*()> CreateInstanceFunc;
    };

    class ClassRegistry {
    public:
        static std::unordered_map<std::string, ClassType>& GetRegistry()
        {
            static std::unordered_map<std::string, ClassType> registry;

            return registry;
        }

        static std::optional<ClassType> GetClassType(const std::string& className)
        {
            const auto& registry = GetRegistry();
        
            const auto& it = registry.find(className);
            if (it != GetRegistry().end())
            {
                return it->second;
            }
            return {};
        }


        static void RegisterClass(const std::string& name, size_t size, const std::function<void*()>& createFunc)
        {
            GetRegistry()[name] = {name, size, createFunc};
        }

        static void PrintRegistry()
        {
            for (const auto& registry : GetRegistry())
            {
                LOG_INFO(registry.second.Name);
            }
        }
    };

#define REGISTER_CLASS(type)\
struct type##_Registry { \
type##_Registry() { ClassRegistry::RegisterClass(#type, sizeof(type), []() -> void* { return new type(); }); } \
}

#define REGISTER_COMPONENT(type) \
static std::string GetStaticComponentType() { return ClassRegistry::GetClassType(#type)->Name; } \
virtual std::string GetComponentType() const override { return GetStaticComponentType(); } \
REGISTER_CLASS(type)

#define CREATE_COMPONENT_REGISTRY(type)\
namespace _HIDDEN{\
type::type##_Registry type##_Registry_Instance {}; }

    static std::string GetCleanTypeName(const std::string& name)
    {
        std::string result = name;
    
        // Remove "struct " or "class " prefix if present
        const std::string structPrefix = "struct ";
        const std::string classPrefix = "class ";
    
        if (result.find(structPrefix) == 0)
        {
            result = result.substr(structPrefix.length());
        }
        else if (result.find(classPrefix) == 0)
        {
            result = result.substr(classPrefix.length());
        }

        return result;
    }

    template<typename T>
    T* Instantiate()
    {
        auto className = GetCleanTypeName(typeid(T).name());
    
        const auto classType = ClassRegistry::GetClassType(className);

        if(!classType)
        {
            LOG_INFO("This class is not registered! {0}", className);
            ClassRegistry::RegisterClassW(className, sizeof(T), []() -> void* { return new T(); } );
        }
    
        return static_cast<T*>(classType->CreateInstanceFunc());
    }

    template<typename T>
    T* Instantiate(const std::string& className)
    {
        const auto classType = ClassRegistry::GetClassType(className);

        if(!classType)
            return nullptr;

        return static_cast<T*>(classType->CreateInstanceFunc());
    }

    /* template<typename T>
    T* Instantiate(std::string className)
    {
        const auto classType = ClassRegistry::GetClassType(className);
        if(!classType)
            return nullptr;
        T* instance = malloc(classType->Size);
        memset(instance, 0, classType->Size);
        return instance;
    }*/
}