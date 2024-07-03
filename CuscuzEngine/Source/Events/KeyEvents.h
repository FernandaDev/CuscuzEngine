#pragma once

#include "CC_Event.h"

class CC_KeyDownEvent : public CC_Event
{
    int m_KeyCode;
    
public:
    CC_KeyDownEvent(int keyCode) : m_KeyCode(keyCode){}
    ~CC_KeyDownEvent() override = default;
    
    int GetKeyCode() const { return m_KeyCode; }

    static CC_EventType GetStaticType() { return CC_EventType::KeyDown; }
    CC_EventType GetEventType() const override { return GetStaticType(); }
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

class CC_KeyUpEvent : public CC_Event
{
    int m_KeyCode;
    
public:
    CC_KeyUpEvent(int keyCode) : m_KeyCode(keyCode){}
    ~CC_KeyUpEvent() override = default;
    
    int GetKeyCode() const { return m_KeyCode; }

    static CC_EventType GetStaticType() { return CC_EventType::KeyUp; }
    CC_EventType GetEventType() const override { return GetStaticType(); }
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