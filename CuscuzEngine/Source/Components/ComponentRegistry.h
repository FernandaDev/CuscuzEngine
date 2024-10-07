#pragma once

struct ClassType
{
    std::string Name;
    size_t Size;
};

class ComponentRegistry {
public:
    static std::vector<ClassType>& GetRegistry()
    {
        static std::vector<ClassType> registry;

        return registry;
    }

    static std::optional<ClassType> GetClassType(const std::string& className)
    {
        for(const auto& component : GetRegistry())
        {
            if(className == component.Name)
                return component;
        }

        return {};
    }

    static void RegisterComponent(const ClassType& name)
    {
        GetRegistry().emplace_back(name);
    }

    static void PrintRegistry()
    {
        for (const auto& registry : GetRegistry())
        {
            std::cout << registry.Name << std::endl;
        }
    }
};

template<typename T>
T* Instantiate(std::string className)
{
    const auto classType = ComponentRegistry::GetClassType(className);

    if(!classType)
        return nullptr;

    T* instance = malloc(classType->Size);
    memset(instance, 0, classType->Size);

    return instance;
}

#define REGISTER_COMPONENT(type) \
    static std::string_view GetStaticComponentType() { return ComponentRegistry::GetClassType(#type)->Name; } \
    virtual std::string_view GetComponentType() const override { return GetStaticComponentType(); } \
    struct [[nodiscard]] type##_Registry { \
        type##_Registry() { ComponentRegistry::RegisterComponent(ClassType(#type, sizeof(type))); } \
    }
    
#define CREATE_COMPONENT_REGISTRY(type)\
    namespace _HIDDEN{\
    type::type##_Registry [[nodiscard]] type##_Registry_Instance {}; }