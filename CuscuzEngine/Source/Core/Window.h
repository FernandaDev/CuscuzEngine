#pragma once

#include "SDL.h"

class Window
{
	int m_Width;
	int m_Height;
	
	SDL_Window* m_Window{nullptr};

public:
	Window() = delete;
	Window(const char* Name, int Width, int Height);
	~Window();

	const int GetWidth() const { return m_Width; }
	const int GetHeight() const { return m_Height; }
	SDL_Window* GetWindow() const { return m_Window; }
};

