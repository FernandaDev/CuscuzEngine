#pragma once

#include "SDL.h"
#include "Events/CC_Event.h"

class Window
{
	int m_Width;
	int m_Height;
	
	SDL_Window* m_Window{nullptr};
	SDL_GLContext m_Context {};
	
public:
	Window() = delete;
	Window(int width, int height);
	~Window();

	void Init(const char* name);

	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }
	SDL_Window* GetWindow() const { return m_Window; }

	SDL_GLContext GetCurrentContext() const { return m_Context; }

	void OnEvent(CC_Event& event);

private:
	bool OnWindowResized(const class CC_WindowResizeEvent& event);
};

