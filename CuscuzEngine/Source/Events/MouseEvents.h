#pragma once

#include "CC_Event.h"

enum class CC_MouseEventType
{
    Moved,
    ButtonDown,
    ButtonUp
};

class CC_MouseMovedEvent : public CC_Event<CC_MouseEventType>
{
    int m_X, m_Y;
    
public:
    CC_MouseMovedEvent(int X, int Y)
        : CC_Event(CC_MouseEventType::Moved , "MouseMovedEvent"), m_X(X), m_Y(Y) { }
    ~CC_MouseMovedEvent() override = default;

    int GetX() const { return m_X; }
    int GetY() const { return m_Y; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << m_Name << ": (" << m_X << "," << m_Y << ")";
        return ss.str();
    }
};

class CC_MouseButtonDownEvent : public CC_Event<CC_MouseEventType>
{
    int m_Button;
    
public:
    CC_MouseButtonDownEvent(int Button)
        : CC_Event(CC_MouseEventType::ButtonDown , "MouseButtonDownEvent"), m_Button(Button) { }
    ~CC_MouseButtonDownEvent() override = default;

    int GetButton() const { return m_Button; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << m_Name << ": " << m_Button;
        return ss.str();
    }
};

class CC_MouseButtonUpEvent : public CC_Event<CC_MouseEventType>
{
    int m_Button;
    
public:
    CC_MouseButtonUpEvent(int Button)
        : CC_Event(CC_MouseEventType::ButtonUp , "MouseButtonUpEvent"), m_Button(Button) { }
    ~CC_MouseButtonUpEvent() override = default;

    int GetButton() const { return m_Button; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << m_Name << ": " << m_Button;
        return ss.str();
    }
};