#pragma once

#include "CC_Event.h"

namespace Cuscuz
{
    class CC_MouseMovedEvent : public CC_Event
    {
        int m_X, m_Y;
    
    public:
        CC_MouseMovedEvent(int x, int y) : m_X(x), m_Y(y) { }
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
        CC_MouseButtonDownEvent(int button) : m_Button(button) { }
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
        CC_MouseButtonUpEvent(int button) : m_Button(button) { }
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
        CC_MouseScrolledEvent(float x, float y) : m_X(x), m_Y(y) {}
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
}