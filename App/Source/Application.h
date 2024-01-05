#pragma once

#include <iostream>

#include "Window.h"
#include "RendererSystem.h"

class Application 
{
	Window* m_Window;
	RendererSystem* m_RendererSystem;

	bool m_IsRunning = true;

public:
	Application();
	~Application();

	void Run();
};