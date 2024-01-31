#pragma once

#include "CC_Event.h"

enum class CC_WindowEventType
{
    Resize,
    Close
};

class CC_WindowResizeEvent : public CC_Event<CC_WindowEventType>
{
    int m_Width, m_Height;
    
public:
    CC_WindowResizeEvent(int Width, int Height) :
    CC_Event(CC_WindowEventType::Resize, "WindowResizeEvent"),
    m_Width(Width), m_Height(Height) { }
    ~CC_WindowResizeEvent() override = default;

    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << m_Name << ": (" << m_Width << "," << m_Height << ")";
        return ss.str();
    }
};

class CC_WindowCloseEvent : public CC_Event<CC_WindowEventType>
{
public:
    CC_WindowCloseEvent() : CC_Event(CC_WindowEventType::Close, "WindowCloseEvent"){ }
    ~CC_WindowCloseEvent() override = default;

    std::string ToString() const override { return m_Name; }
};