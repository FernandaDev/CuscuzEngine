#pragma once

#include "CC_Event.h"

class CC_MouseMovedEvent : public CC_Event
{
    int m_X, m_Y;
    
public:
    CC_MouseMovedEvent(int X, int Y) : m_X(X), m_Y(Y) { }
    ~CC_MouseMovedEvent() override = default;
    
    int GetX() const { return m_X; }
    int GetY() const { return m_Y; }

    static CC_EventType GetStaticType() { return CC_EventType::MouseMoved; }
    CC_EventType GetEventType() const override { return GetStaticType(); }
    const char* GetName() const override { return "MouseMoved"; }

    int GetCategoryFlags() const override
    { return EventCategory::EventCategoryMouse; }
        
    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << "x: " << m_X << " y: " << m_Y;
        return ss.str();
    }
};

class CC_MouseButtonDownEvent : public CC_Event
{
    int m_Button;
    
public:
    CC_MouseButtonDownEvent(int Button) : m_Button(Button) { }
    ~CC_MouseButtonDownEvent() override = default;
    
    int GetButton() const { return m_Button; }

    static CC_EventType GetStaticType() { return CC_EventType::MouseButtonDown; }
    CC_EventType GetEventType() const override { return GetStaticType(); }
    const char* GetName() const override { return "MouseButtonDown"; }

    int GetCategoryFlags() const override
    { return EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput; }
    
    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonDownEvent: " << m_Button;
        return ss.str();
    }
};

class CC_MouseButtonUpEvent : public CC_Event
{
    int m_Button;
    
public:
    CC_MouseButtonUpEvent(int Button) : m_Button(Button) { }
    ~CC_MouseButtonUpEvent() override = default;
    
    int GetButton() const { return m_Button; }

    static CC_EventType GetStaticType() { return CC_EventType::MouseButtonUp; }
    CC_EventType GetEventType() const override { return GetStaticType(); }
    const char* GetName() const override { return "MouseButtonUp"; }

    int GetCategoryFlags() const override
    { return EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput; }
    
    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonUpEvent:" << m_Button;
        return ss.str();
    }
};

class CC_MouseScrolledEvent : public CC_Event
{
    float m_X, m_Y;
    
public:
    CC_MouseScrolledEvent(float X, float Y) : m_X(X), m_Y(Y) {}
    ~CC_MouseScrolledEvent() override = default;
    
    float GetX() const { return m_X; }
    float GetY() const { return m_Y; }

    static CC_EventType GetStaticType() { return CC_EventType::MouseScrolled; }
    CC_EventType GetEventType() const override { return GetStaticType(); }
    const char* GetName() const override { return "MouseScrolled"; }

    int GetCategoryFlags() const override
    { return EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput; }
    
    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseScrolledEvent" << ": (" << m_X << "," << m_Y << ")";
        return ss.str();
    }
};