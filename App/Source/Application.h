#pragma once

#include <iostream>

#include "Window.h"

class Application 
{
	Window* m_Window;
	SDL_Renderer* m_Renderer;

	bool m_IsRunning = true;

public:
	Application();
	~Application();

	void Run();
};