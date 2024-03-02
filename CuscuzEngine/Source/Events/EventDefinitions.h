#pragma once

#include "CC_EventDispatcher.h"

#define DECLARE_EVENT(EventName, ...) \
class EventName {\
public:\
    using DelegateType = std::function<void(__VA_ARGS__)>;\
    template<typename T>\
    void Add(T* instance, void (T::*func)(__VA_ARGS__)) {\
        auto del = std::bind(func, instance, std::placeholders::_1);\
        delegates.emplace_back(del, instance);\
    }\
    template<typename T>\
    void Remove(T* instance) {\
        const DelegateWrapper wrapper(nullptr, instance);\
        auto it = std::remove(delegates.begin(), delegates.end(), wrapper);\
        if (it != delegates.end()) {\
            delegates.erase(it, delegates.end());\
        }\
    }\
    void Broadcast(__VA_ARGS__ args) const {\
        for (const auto& d : delegates) {\
            d.delegate(args);\
        }\
    }\
private:\
    struct DelegateWrapper {\
        DelegateType delegate;\
        void* instance;\
        DelegateWrapper(DelegateType del, void* inst)\
            : delegate(std::move(del)), instance(inst) {}\
        bool operator==(const DelegateWrapper& other) const {\
            return instance == other.instance;\
        }\
    };\
    std::vector<DelegateWrapper> delegates;\
};