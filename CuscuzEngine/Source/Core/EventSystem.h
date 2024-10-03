#pragma once

#include "Events/EventDefinitions.h"
#include "SDL.h"

class EventSystem
{
public:
	using EventCallbackFn = std::function<void(CC_Event&)>;

private:
	EventCallbackFn m_EventCallbackFn;
	
public:
	EventSystem() = default;
	~EventSystem() = default;

	void SetEventCallback(const EventCallbackFn& callback);

	void Update() const;
};
