#pragma once

#include "EventDispatcher.h"

namespace Cuscuz
{
    #define DECLARE_EVENT_NO_ARGS(EventName) \
    class EventName {\
    public:\
        using DelegateType = std::function<void()>;\
        template<typename T>\
        void Add(T* instance, void (T::*func)()) {\
            auto del = std::bind(func, instance);\
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
        void Broadcast() const {\
            for (const auto& d : delegates) {\
                d.delegate();\
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

    #define DECLARE_EVENT_ONE_ARG(EventName, argType1, argName1) \
    class EventName {\
    public:\
        using DelegateType = std::function<void(argType1 argName1)>;\
        template<typename T>\
        void Add(T* instance, void (T::*func)(argType1 argName1))\
        {\
            auto del = std::bind(func, instance, std::placeholders::_1);\
            delegates.emplace_back(del, instance);\
        }\
        template<typename T>\
        void Remove(T* instance)\
        {\
            const DelegateWrapper wrapper(nullptr, instance);\
            auto it = std::remove(delegates.begin(), delegates.end(), wrapper);\
            if (it != delegates.end()) {\
                delegates.erase(it, delegates.end());\
            }\
        }\
        void Broadcast(argType1 argName1) const\
        {\
            for (const auto& d : delegates) {\
                d.delegate(argName1);\
            }\
        }\
        \
        private:\
        struct DelegateWrapper\
        {\
            DelegateType delegate;\
            void* instance;\
            \
            DelegateWrapper(DelegateType del, void* inst)\
            : delegate(std::move(del)), instance(inst) {}\
            bool operator==(const DelegateWrapper& other) const\
            {\
                return instance == other.instance;\
            }\
        };\
        \
        std::vector<DelegateWrapper> delegates;\
    };

    #define DECLARE_EVENT_TWO_ARGS(EventName, argType1, argName1, argType2, argName2) \
    class EventName {\
    public:\
        using DelegateType = std::function<void(argType1 argName1, argType2 argName2)>;\
        template<typename T>\
        void Add(T* instance, void (T::*func)(argType1, argType2))\
        {\
            auto del = std::bind(func, instance,  std::placeholders::_1, std::placeholders::_2);\
            delegates.emplace_back(del, instance);\
        }\
        template<typename T>\
        void Remove(T* instance)\
        {\
            const DelegateWrapper wrapper(nullptr, instance);\
            auto it = std::remove(delegates.begin(), delegates.end(), wrapper);\
            if (it != delegates.end()) {\
                delegates.erase(it, delegates.end());\
            }\
        }\
        void Broadcast(argType1 argName1, argType2 argName2) const\
        {\
            for (const auto& d : delegates) {\
                d.delegate(argName1, argName2);\
            }\
        }\
        \
        private:\
        struct DelegateWrapper\
        {\
            DelegateType delegate;\
            void* instance;\
            \
            DelegateWrapper(DelegateType del, void* inst)\
            : delegate(std::move(del)), instance(inst) {}\
            bool operator==(const DelegateWrapper& other) const\
            {\
                return instance == other.instance;\
            }\
        };\
        \
        std::vector<DelegateWrapper> delegates;\
    };
    
    #define DECLARE_EVENT_THREE_ARGS(EventName, argType1, argName1, argType2, argName2, argType3, argName3) \
    class EventName {\
    public:\
        using DelegateType = std::function<void(argType1 argName1, argType2 argName2, argType3 argName3)>;\
        template<typename T>\
        void Add(T* instance, void (T::*func)(argType1, argType2, argType3))\
        {\
            auto del = std::bind(func, instance,  std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);\
            delegates.emplace_back(del, instance);\
        }\
        template<typename T>\
        void Remove(T* instance)\
        {\
            const DelegateWrapper wrapper(nullptr, instance);\
            auto it = std::remove(delegates.begin(), delegates.end(), wrapper);\
            if (it != delegates.end()) {\
                delegates.erase(it, delegates.end());\
            }\
        }\
        void Broadcast(argType1 argName1, argType2 argName2, argType3 argName3) const\
        {\
            for (const auto& d : delegates) {\
                d.delegate(argName1, argName2, argName3);\
            }\
        }\
        \
    private:\
        struct DelegateWrapper\
        {\
            DelegateType delegate;\
            void* instance;\
        \
            DelegateWrapper(DelegateType del, void* inst)\
            : delegate(std::move(del)), instance(inst) {}\
            bool operator==(const DelegateWrapper& other) const\
            {\
                return instance == other.instance;\
            }\
        };\
        \
        std::vector<DelegateWrapper> delegates;\
    };

    #define DECLARE_EVENT_FOUR_ARGS(EventName, argType1, argName1, argType2, argName2,\
                                    argType3, argName3, argType4, argName4) \
    class EventName {\
    public:\
        using DelegateType = std::function<void(argType1 argName1, argType2 argName2,\
                                                argType3 argName3, argType4 argName4)>;\
        template<typename T>\
        void Add(T* instance, void (T::*func)(argType1, argType2, argType3, argType4))\
        {\
            auto del = std::bind(func, instance, std::placeholders::_1, std::placeholders::_2,\
                                                 std::placeholders::_3, std::placeholders::_4);\
            _delegates.emplace_back(del, instance);\
        }\
        template<typename T>\
        void Remove(T* instance)\
        {\
            const DelegateWrapper wrapper(nullptr, instance);\
            auto it = std::remove(_delegates.begin(), _delegates.end(), wrapper);\
            if (it != _delegates.end()) {\
                _delegates.erase(it, _delegates.end());\
            }\
        }\
        void Broadcast(argType1 argName1, argType2 argName2, argType3 argName3, argType4 argName4) const\
        {\
            for (const auto& _d : _delegates) {\
                _d.delegate(argName1, argName2, argName3, argName4);\
            }\
        }\
        \
    private:\
        struct DelegateWrapper\
        {\
            DelegateType delegate;\
            void* instance;\
            \
            DelegateWrapper(DelegateType del, void* inst)\
            : delegate(std::move(del)), instance(inst) {}\
            bool operator==(const DelegateWrapper& other) const\
            {\
                return instance == other.instance;\
            }\
        };\
        \
        std::vector<DelegateWrapper> _delegates;\
    };
    
}
