#pragma once

#include "Cuscuz/Utils/Hash.h"

namespace Cuscuz
{
#define DECLARE_CLASS_TYPE(className) \
    static constexpr uint32_t StaticTypeID() { return fnv1a_32(#className); } \
    uint32_t GetTypeID() const override { return StaticTypeID(); } \
    static constexpr std::string_view StaticClassName() { return #className; }\
    std::string_view ClassName() override { return StaticClassName(); }

#define TYPE_OF(Type) \
    (Type::ClassTypeID)

    class ObjectBase
    {
    public:
        virtual ~ObjectBase() = default;
        
        virtual uint32_t GetTypeID() const = 0;
        virtual std::string_view ClassName() = 0;
        
        template <typename T>
        T* As()
        {
            return static_cast<T*>(CastToTypePtr(T::StaticTypeID()));
        }

        template <typename T>
        const T* As() const
        {
            // const_cast here to support a single CastToTypePtr function  
            return static_cast<const T*>(const_cast<ObjectBase*>(this)->CastToTypePtr(T::StaticTypeID()));
        }

        bool Is(uint32_t typeID) { return typeID == GetTypeID(); }

        template <typename T>
        bool Is() { return T::StaticTypeID() == GetTypeID(); }

        bool IsA(uint32_t typeID) { return CastToTypePtr(typeID) != nullptr; }
        
        template <typename T>
        bool IsA() { return CastToTypePtr(T::StaticTypeID()) != nullptr; }

    protected:
        virtual void* CastToTypePtr(uint32_t typeID) = 0;
    };

#define CLASS_TYPE_IMPLEMENT(className) \
    virtual void* CastToTypePtr(uint32_t typeID) override \
    {                                                     \
        if (typeID == StaticTypeID())                     \
            return this;                                  \
                                                          \
        return nullptr;                                   \
    }  

#define CLASS_TYPE_IMPLEMENT_WITH_BASE(className, base)\
    virtual void* CastToTypePtr(uint32_t typeID) override \
    {                                                     \
        if(typeID == StaticTypeID())                      \
            return this;                                  \
        return base::CastToTypePtr(typeID);               \
    }
}
