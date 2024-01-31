#pragma once

#include "CC_Event.h"

enum class CC_KeyEventType
{
    Down,
    Up
};

class CC_KeyDownEvent : public CC_Event<CC_KeyEventType>
{
    int m_KeyCode;
    
public:
    CC_KeyDownEvent(int KeyCode) :
    CC_Event(CC_KeyEventType::Down, "KeyDownEvent"), m_KeyCode(KeyCode){}
    ~CC_KeyDownEvent() override = default;

    int GetKeyCode() const { return m_KeyCode; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << m_Name << ": " << m_KeyCode;
        return ss.str();
    }
};

class CC_KeyUpEvent : public CC_Event<CC_KeyEventType>
{
    int m_KeyCode;
    
public:
    CC_KeyUpEvent(int KeyCode) :
    CC_Event(CC_KeyEventType::Up, "KeyUpEvent"), m_KeyCode(KeyCode){}
    ~CC_KeyUpEvent() override = default;

    int GetKeyCode() const { return m_KeyCode; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << m_Name << ": " << m_KeyCode;
        return ss.str();
    }
};