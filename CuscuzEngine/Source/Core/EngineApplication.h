#pragma once

#include "Window.h"
#include "RendererSystem.h"
#include "EventSystem.h"
#include "Events/CC_Event.h"
#include "Events/WindowEvents.h"

constexpr Uint32 FramesPerSecond = 30;

class EngineApplication 
{
	bool m_IsRunning = true;

public:
	EngineApplication();
	virtual ~EngineApplication();

	static EngineApplication& Get() { return *s_Instance;}
	
	void Run();
	
	virtual void Start();
	virtual void Update();

	Window* CC_Window;
	RendererSystem* CC_RendererSystem;
	EventSystem* CC_EventSystem;

protected:
	virtual void Render() const;
private:
	void Quit(const CC_Event<CC_WindowEventType>& Event);
	void ProcessInput() const;

	static EngineApplication* s_Instance;
	friend int ::main(int argc, char* argv[]);
};