#pragma once

class ComponentRegistry {
public:
    static std::vector<std::string>& GetRegistry() {
        static std::vector<std::string> registry;
        return registry;
    }

    static void RegisterComponent(const std::string& name) {
        GetRegistry().emplace_back(name);
    }

    static void PrintRegistry() {
        for (const auto& name : GetRegistry()) {
            std::cout << name << std::endl;
        }
    }
};

#define REGISTER_COMPONENT(type) \
    static std::string_view GetStaticComponentType() { return #type; } \
    virtual std::string_view GetComponentType() const override { return GetStaticComponentType(); } \
    static struct type##_Registry { \
        type##_Registry() { ComponentRegistry::RegisterComponent(#type); } \
    } type##_Registry_Instance
    

// #define REGISTER_COMPONENT(type) \
// static std::string_view GetStaticComponentType() { return #type; } \
// virtual std::string_view GetComponentType() const override { return GetStaticComponentType(); } \
// struct type##_Registry { \
// type##_Registry() { ComponentRegistry::RegisterComponent(#type); } \
// }; \
// static type##_Registry registry