#pragma once

#include "SDL.h"
#include "Events/CC_Event.h"
#include "Events/WindowEvents.h"

class Window
{
	int m_Width;
	int m_Height;
	
	SDL_Window* m_Window{nullptr};

public:
	Window() = delete;
	Window(const char* Name, int Width, int Height);
	~Window();

	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }
	SDL_Window* GetWindow() const { return m_Window; }

private:
	void OnWindowResized(const CC_Event<CC_WindowEventType>& Event);
	
};

