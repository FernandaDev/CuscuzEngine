#pragma once

#include "Event.h"

enum class WindowEventType
{
    Resize,
    Close
};

class WindowResizeEvent : public Event<WindowEventType>
{
    int m_Width, m_Height;
    
public:
    WindowResizeEvent(int Width, int Height) :
    Event(WindowEventType::Resize, "WindowResizeEvent"),
    m_Width(Width), m_Height(Height) { }
    ~WindowResizeEvent() override = default;

    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << m_Name << ": (" << m_Width << "," << m_Height << ")";
        return ss.str();
    }
};

class WindowCloseEvent : public Event<WindowEventType>
{
public:
    WindowCloseEvent() : Event(WindowEventType::Close, "WindowCloseEvent"){ }
    ~WindowCloseEvent() override = default;

    std::string ToString() const override { return m_Name; }
};