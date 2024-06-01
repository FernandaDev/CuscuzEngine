#pragma once

#include "Window.h"
#include "RendererSystem.h"
#include "EventSystem.h"
#include "Events/CC_Event.h"
#include "Events/WindowEvents.h"
#include "CC_Game.h"
#include "GUI/CC_ImGuiLayer.h"

constexpr Uint32 FramesPerSecond = 30;

class EngineApplication 
{
public:
	Window* CC_Window;
	RendererSystem* CC_RendererSystem;
	EventSystem* CC_EventSystem;

protected:
	CC_Game* m_Game;
	
private:
	static EngineApplication* s_Instance;
	CC_ImGuiLayer m_ImGuiLayer;
	
	bool m_IsRunning = true;

public:
	EngineApplication();
	EngineApplication(CC_Game* Game);
	virtual ~EngineApplication();

	static EngineApplication& Get() { return *s_Instance;}
	
	void Run();
	
	virtual void Start();
	virtual void Update();

protected:
	virtual void Render();
private:
	void Init();
	void Quit(const CC_Event<CC_WindowEventType>& Event);
	void ProcessInput() const;

	friend int ::main(int argc, char* argv[]);
	friend class CC_ImGuiLayer;
};
