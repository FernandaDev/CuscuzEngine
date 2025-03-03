#pragma once

#include "CuscuzEvent.h"

namespace Cuscuz
{
    class CC_WindowResizeEvent : public CuscuzEvent
    {
        int m_Width, m_Height;
     
    public:
        CC_WindowResizeEvent(int width, int height) : m_Width(width), m_Height(height) {}
        ~CC_WindowResizeEvent() override = default;

        int GetWidth() const { return m_Width; }
        int GetHeight() const { return m_Height; }

        static CuscuzEventType GetStaticType() { return CuscuzEventType::WindowResize; }
        CuscuzEventType GetEventType() const override { return GetStaticType(); }
        const char* GetName() const override { return "WindowResize"; }

        int GetCategoryFlags() const override
        {
            return EventCategory::EventCategoryApplication;
        }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: (" << m_Width << "," << m_Height << ")";
            return ss.str();
        }
    };

    class CC_WindowCloseEvent : public CuscuzEvent
    {
    public:
        CC_WindowCloseEvent() = default;
        ~CC_WindowCloseEvent() override = default;

        static CuscuzEventType GetStaticType() { return CuscuzEventType::WindowClose; }
        CuscuzEventType GetEventType() const override { return GetStaticType(); }
        const char* GetName() const override { return "WindowClose"; }

        int GetCategoryFlags() const override
        { return EventCategory::EventCategoryApplication; }
     
        std::string ToString() const override { return "WindowCloseEvent"; }
    };

    class CC_WindowMinimizedEvent : public CuscuzEvent
    {
    public:
        CC_WindowMinimizedEvent() = default;
        ~CC_WindowMinimizedEvent() override = default;

        static CuscuzEventType GetStaticType() { return CuscuzEventType::WindowUnfocused; }
        CuscuzEventType GetEventType() const override { return GetStaticType(); }
        const char* GetName() const override { return "WindowMinimized"; }
    
        int GetCategoryFlags() const override
        { return EventCategory::EventCategoryApplication; }

        std::string ToString() const override { return "WindowMinimizedEvent"; }
    };

    class CC_WindowRestoredFocusEvent : public CuscuzEvent
    {
    public:
        CC_WindowRestoredFocusEvent() = default;
        ~CC_WindowRestoredFocusEvent() override = default;

        static CuscuzEventType GetStaticType() { return CuscuzEventType::WindowFocused; }
        CuscuzEventType GetEventType() const override { return GetStaticType(); }
        const char* GetName() const override { return "WindowFocused"; }
    
        int GetCategoryFlags() const override
        { return EventCategory::EventCategoryApplication; }

        std::string ToString() const override { return "WindowRestoredEvent"; }
    };
}