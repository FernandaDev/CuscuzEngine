#pragma once

#include "CC_Event.h"

enum class CC_MouseEventType
{
    Moved,
    ButtonDown,
    ButtonUp,
    Scroll,
};

class CC_MouseMovedEvent : public CC_Event<CC_MouseEventType>
{
    int m_X, m_Y;
    
public:
    CC_MouseMovedEvent(int X, int Y)
        : CC_Event(CC_MouseEventType::Moved , "MouseMovedEvent"), m_X(X), m_Y(Y) { }
    ~CC_MouseMovedEvent() override = default;
    CC_MouseMovedEvent(const CC_MouseMovedEvent& other) :
    CC_Event(other), m_X(other.m_X), m_Y(other.m_Y){}

    CC_MouseMovedEvent& operator=(const CC_MouseMovedEvent& other)
    {
        if(this != &other)
        {
            CC_Event::operator=(other);
            m_X = other.m_X;
            m_Y = other.m_Y;
        }
        
        return *this;
    }

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

    CC_MouseButtonDownEvent(const CC_MouseButtonDownEvent& other) :
        CC_Event(other), m_Button(other.m_Button){}

    CC_MouseButtonDownEvent& operator=(const CC_MouseButtonDownEvent& other)
    {
        if(this != &other)
        {
            CC_Event::operator=(other);
            m_Button = other.m_Button;
        }
        
        return *this;
    }
    
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

    CC_MouseButtonUpEvent(const CC_MouseButtonUpEvent& other) :
            CC_Event(other), m_Button(other.m_Button){}

    CC_MouseButtonUpEvent& operator=(const CC_MouseButtonUpEvent& other)
    {
        if(this != &other)
        {
            CC_Event::operator=(other);
            m_Button = other.m_Button;
        }
        
        return *this;
    }
    
    int GetButton() const { return m_Button; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << m_Name << ": " << m_Button;
        return ss.str();
    }
};

class CC_MouseScrollEvent : public CC_Event<CC_MouseEventType>
{
    float m_X, m_Y;
    
public:
    CC_MouseScrollEvent(float X, float Y)
        : CC_Event(CC_MouseEventType::Scroll, "MouseScrollEvent"), m_X(X), m_Y(Y)
    {}
    ~CC_MouseScrollEvent() override = default;

    CC_MouseScrollEvent(const CC_MouseScrollEvent& other) :
        CC_Event(other), m_X(other.m_X), m_Y(other.m_Y){}

    CC_MouseScrollEvent& operator=(const CC_MouseScrollEvent& other)
    {
        if(this != &other)
        {
            CC_Event::operator=(other);
            m_X = other.m_X;
            m_Y = other.m_Y;
        }
        
        return *this;
    }

    
    float GetX() const { return m_X; }
    float GetY() const { return m_Y; }
    
    std::string ToString() const override
    {
        std::stringstream ss;
        ss << m_Name << ": (" << m_X << "," << m_Y << ")";
        return ss.str();
    }
};