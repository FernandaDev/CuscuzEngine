#pragma once

#include "CC_Event.h"

class CC_WindowResizeEvent : public CC_Event
 {
     int m_Width, m_Height;
     
 public:
     CC_WindowResizeEvent(int width, int height) : m_Width(width), m_Height(height) {}
     ~CC_WindowResizeEvent() override = default;

     int GetWidth() const { return m_Width; }
     int GetHeight() const { return m_Height; }

     static CC_EventType GetStaticType() { return CC_EventType::WindowResize; }
     CC_EventType GetEventType() const override { return GetStaticType(); }
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

 class CC_WindowCloseEvent : public CC_Event
 {
 public:
     CC_WindowCloseEvent() = default;
     ~CC_WindowCloseEvent() override = default;

     static CC_EventType GetStaticType() { return CC_EventType::WindowClose; }
     CC_EventType GetEventType() const override { return GetStaticType(); }
     const char* GetName() const override { return "WindowClose"; }

     int GetCategoryFlags() const override
     { return EventCategory::EventCategoryApplication; }
     
     std::string ToString() const override { return "WindowCloseEvent"; }
 };