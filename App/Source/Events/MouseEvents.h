#pragma once

#include "Event.h"

enum class MouseEventType
{
    Moved,
    ButtonDown,
    ButtonUp
};

class MouseMovedEvent : public Event<MouseEventType>
{
    int m_X, m_Y;
    
public:
    MouseMovedEvent(int X, int Y)
        : Event(MouseEventType::Moved , "MouseMovedEvent"), m_X(X), m_Y(Y) { }
    ~MouseMovedEvent() override = default;

    int GetX() const { return m_X; }
    int GetY() const { return m_Y; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << m_Name << ": (" << m_X << "," << m_Y << ")";
        return ss.str();
    }
};

class MouseButtonDownEvent : public Event<MouseEventType>
{
    int m_Button;
    
public:
    MouseButtonDownEvent(int Button)
        : Event(MouseEventType::ButtonDown , "MouseButtonDownEvent"), m_Button(Button) { }
    ~MouseButtonDownEvent() override = default;

    int GetButton() const { return m_Button; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << m_Name << ": " << m_Button;
        return ss.str();
    }
};

class MouseButtonUpEvent : public Event<MouseEventType>
{
    int m_Button;
    
public:
    MouseButtonUpEvent(int Button)
        : Event(MouseEventType::ButtonUp , "MouseButtonUpEvent"), m_Button(Button) { }
    ~MouseButtonUpEvent() override = default;

    int GetButton() const { return m_Button; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << m_Name << ": " << m_Button;
        return ss.str();
    }
};