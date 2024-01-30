#pragma once

#include "Event.h"

enum class KeyEventType
{
    Down,
    Up
};

class KeyDownEvent : public Event<KeyEventType>
{
    int m_KeyCode;
    
public:
    KeyDownEvent(int KeyCode) :
    Event(KeyEventType::Down, "KeyDownEvent"), m_KeyCode(KeyCode){}
    ~KeyDownEvent() override = default;

    int GetKeyCode() const { return m_KeyCode; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << m_Name << ": " << m_KeyCode;
        return ss.str();
    }
};

class KeyUpEvent : public Event<KeyEventType>
{
    int m_KeyCode;
    
public:
    KeyUpEvent(int KeyCode) :
    Event(KeyEventType::Up, "KeyUpEvent"), m_KeyCode(KeyCode){}
    ~KeyUpEvent() override = default;

    int GetKeyCode() const { return m_KeyCode; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << m_Name << ": " << m_KeyCode;
        return ss.str();
    }
};