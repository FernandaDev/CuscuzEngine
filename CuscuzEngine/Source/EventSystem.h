#pragma once

#include "Events/EventDefinitions.h"
#include "SDL.h"

DECLARE_EVENT(OnSDLEventDelegate, const SDL_Event&)

class EventSystem
{
public:
	using EventCallbackFn = std::function<void(CC_Event&)>;

private:
	OnSDLEventDelegate m_SDLEventDelegate;
	EventCallbackFn m_EventCallbackFn;
	
public:
	EventSystem() = default;
	~EventSystem() = default;

	void SetEventCallback(const EventCallbackFn& callback);

	OnSDLEventDelegate& GetSDLEventDelegate()
	{
		return m_SDLEventDelegate;
	}

	void Update() const;
};
