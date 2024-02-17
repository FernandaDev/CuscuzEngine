#pragma once

#include "Events/EventDefinitions.h"
#include "SDL.h"

DECLARE_EVENT(OnSDLEventDelegate, const SDL_Event&)

class EventSystem
{
	OnSDLEventDelegate m_SDLEventDelegate;
	
public:
	EventSystem() = default;
	~EventSystem() = default;

	OnSDLEventDelegate& GetSDLEventDelegate()
	{
		return m_SDLEventDelegate;
	}

	void Update();
};
