#pragma once

struct ComponentInfo
{
    std::string Name;
    size_t Size;
};

class ComponentRegistry {
public:
    static std::vector<ComponentInfo>& GetRegistry()
    {
        static std::vector<ComponentInfo> registry;
        return registry;
    }

    static std::optional<ComponentInfo> GetComponentInfo(const std::string& className)
    {
        for(const auto& component : GetRegistry())
        {
            if(className == component.Name)
                return component;
        }

        return {};
    }

    static void RegisterComponent(const ComponentInfo& name)
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
    auto componentInfo = ComponentRegistry::GetComponentInfo(className);

    if(!componentInfo)
        return nullptr;

    T* instance = malloc(componentInfo->Size);
    memset(instance, 0, componentInfo->Size);

    return instance;
}

#define REGISTER_COMPONENT(type) \
    static std::string_view GetStaticComponentType() { return #type; } \
    virtual std::string_view GetComponentType() const override { return GetStaticComponentType(); } \
    struct [[nodiscard]] type##_Registry { \
        type##_Registry() { ComponentRegistry::RegisterComponent(ComponentInfo(#type, sizeof(type))); } \
    }
    
#define CREATE_COMPONENT_REGISTRY(type)\
    static type::type##_Registry [[nodiscard]] type##_Registry_Instance {}