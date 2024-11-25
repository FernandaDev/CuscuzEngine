#pragma once

#include "SDL.h"
#include "Events/CC_Event.h"

class GraphicsContext;

class Window
{
	int m_Width;
	int m_Height;
	
	SDL_Window* m_Window{nullptr};
	std::unique_ptr<GraphicsContext> m_Context{};
	
public:
	Window() = delete;
	Window(int width, int height);
	~Window();

	void Init(const char* name);
	void OnEvent(CC_Event& event);
	void Render();

	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }
	SDL_Window* GetWindow() const { return m_Window; }

	GraphicsContext* GetContext() const { return m_Context.get(); }


private:
	bool OnWindowResized(const class CC_WindowResizeEvent& event);
};

