#pragma once

#include "Events/Event.h"
#include "Events/KeyEvents.h"
#include "Events/EventHandler.h"
#include "SDL.h"

class EventSystem
{
	const Uint8* m_CurrentState;

public:
	EventSystem() = default;
	~EventSystem() = default;

	void Start();
	void Update();
	bool IsKeyDown(const SDL_Scancode& Input);
	
private:
	void RefreshKeyState();

	void OnKeyDown(const Event<KeyEventType>& Event);
	void OnKeyUp(const Event<KeyEventType>& Event);
	void OnMouseButtonDown(const Event<MouseEventType>& Event);
	void OnMouseButtonUp(const Event<MouseEventType>& Event);
	void OnMouseMoved(const Event<MouseEventType>& Event);
};
