#pragma once

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
            std::cout << registry.second.Name << std::endl;
        }
    }
};

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

#define REGISTER_CLASS(type)\
    struct [[nodiscard]] type##_Registry { \
    type##_Registry() { ClassRegistry::RegisterClass(#type, sizeof(type), []() -> void* { return new type(); }); } \
    }

#define REGISTER_COMPONENT(type) \
    static std::string GetStaticComponentType() { return ClassRegistry::GetClassType(#type)->Name; } \
    virtual std::string GetComponentType() const override { return GetStaticComponentType(); } \
    REGISTER_CLASS(type)

#define CREATE_COMPONENT_REGISTRY(type)\
    namespace _HIDDEN{\
    type::type##_Registry [[nodiscard]] type##_Registry_Instance {}; }