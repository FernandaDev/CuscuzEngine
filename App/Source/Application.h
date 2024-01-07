#pragma once

#include "Window.h"
#include "RendererSystem.h"
#include "EventSystem.h"
#include "Events/Event.h"
#include "Events/WindowEvents.h"

class Application 
{
	Window* m_Window;
	RendererSystem* m_RendererSystem;
	EventSystem* m_EventSystem;

	bool m_IsRunning = true;

public:
	Application();
	~Application();

	void Quit(const Event<WindowEventType>& Event);
	
	void Run() const;
};
