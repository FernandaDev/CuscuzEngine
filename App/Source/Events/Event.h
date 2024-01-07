#pragma once

#include <string>
#include <sstream>

template<typename T>
class Event 
{
public:
	Event() = default;
	Event(T Type, const char* Name = "") : m_Type{Type}, m_Name{Name} {}
	virtual ~Event() = default;

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