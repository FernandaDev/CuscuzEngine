#pragma once

#include "CuscuzEvent.h"

namespace Cuscuz
{
    class CC_KeyDownEvent : public CuscuzEvent
    {
        int m_KeyCode;
    
    public:
        CC_KeyDownEvent(int keyCode) : m_KeyCode(keyCode){}
        ~CC_KeyDownEvent() override = default;
    
        int GetKeyCode() const { return m_KeyCode; }

        static CuscuzEventType GetStaticType() { return CuscuzEventType::KeyDown; }
        CuscuzEventType GetEventType() const override { return GetStaticType(); }
        const char* GetName() const override { return "KeyDown"; }

        int GetCategoryFlags() const override
        { return EventCategory::EventCategoryInput | EventCategory::EventCategoryKeyboard ; }
    
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyDownEvent:" << m_KeyCode;
            return ss.str();
        }
    };

    class CC_KeyUpEvent : public CuscuzEvent
    {
        int m_KeyCode;
    
    public:
        CC_KeyUpEvent(int keyCode) : m_KeyCode(keyCode){}
        ~CC_KeyUpEvent() override = default;
    
        int GetKeyCode() const { return m_KeyCode; }

        static CuscuzEventType GetStaticType() { return CuscuzEventType::KeyUp; }
        CuscuzEventType GetEventType() const override { return GetStaticType(); }
        const char* GetName() const override { return "KeyUp"; }

        int GetCategoryFlags() const override
        { return EventCategory::EventCategoryInput | EventCategory::EventCategoryKeyboard ; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyUpEvent: " << m_KeyCode;
            return ss.str();
        }
    };
}