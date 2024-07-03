#pragma once

#include "SDL.h"
#include "Events/CC_Event.h"

class Window
{
	int m_Width;
	int m_Height;
	
	SDL_Window* m_Window{nullptr};

public:
	Window() = delete;
	Window(const char* name, int width, int height);
	~Window();

	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }
	SDL_Window* GetWindow() const { return m_Window; }

	void OnEvent(CC_Event& event);

private:
	bool OnWindowResized(const class CC_WindowResizeEvent& event);
};

