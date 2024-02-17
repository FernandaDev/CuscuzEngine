#pragma once

#include "CC_EventDispatcher.h"

#define DECLARE_EVENT(EventName, ...) \
    class EventName { \
    public: \
    using DelegateType = std::function<void(__VA_ARGS__)>; \
    void Add(const DelegateType& del) { delegates.push_back(del); } \
    template<typename T> \
    void Add(T* instance, void (T::*func)(__VA_ARGS__)) { \
    Add(std::bind(func, instance, std::placeholders::_1)); \
    } \
    void Broadcast(__VA_ARGS__ args) const { \
    for (const auto& d : delegates) { \
        d(args); \
    } \
    } \
    private: \
    std::vector<DelegateType> delegates; \
};