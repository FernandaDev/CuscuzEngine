#pragma once

#include "pch.h"

template<typename T>
class CC_Event 
{
public:
	CC_Event() = default;
	CC_Event(T Type, const char* Name) :
	m_Type{Type}, m_Name{Name}
	{}
	virtual ~CC_Event() = default;

	CC_Event(const CC_Event& other) :
	m_Type{other.m_Type}, m_Name{other.m_Name}, m_Handled(other.m_Handled)
	{}
	
	CC_Event& operator=(const CC_Event& other)
	{
		if(this != &other)
		{
			m_Type = other.m_Type;
			m_Name = other.m_Name;
			m_Handled = other.m_Handled;
		}

		return *this;
	}

	const T& GetType() const { return m_Type; }
	virtual std::string ToString() const = 0;

	template<typename EventType>
	EventType ToType() const { return static_cast<const EventType&>(*this); }

	bool Handled() const { return m_Handled; }

protected:
	T m_Type;
	std::string m_Name;
	bool m_Handled = false;
};