#include "pch.h"
#include "SDL.h"

#include "EngineApplication.h"

#include "ResourceManager.h"
#include "Core/Time.h"
#include "Events/EventHandler.h"
#include "Events/WindowEvents.h"
#include "Utils/Log.h"

enum
{
	SCREEN_WIDTH = 1280,
	SCREEN_HEIGHT = 720
};

EngineApplication* EngineApplication::s_Instance = nullptr;

EngineApplication::EngineApplication() :
	CC_Window{ new Window("Game", SCREEN_WIDTH, SCREEN_HEIGHT) },
	CC_RendererSystem { new RendererSystem {CC_Window}},
	CC_EventSystem{ new EventSystem() },	
	m_ImGuiLayer{*CC_Window, CC_RendererSystem->GetRenderer()}
{
	Init();	
}

EngineApplication::EngineApplication(CC_Game* Game) :
	CC_Window{ new Window("Game", SCREEN_WIDTH, SCREEN_HEIGHT) },
	CC_RendererSystem { new RendererSystem {CC_Window}},
	CC_EventSystem{ new EventSystem() },
	m_Game(Game),
	m_ImGuiLayer{*CC_Window, CC_RendererSystem->GetRenderer()}
{
	Init();
}

void EngineApplication::Init()
{
	SUBSCRIBE_WINDOW_EVENT(CC_WindowEventType::Close, this, EngineApplication::Quit);
	s_Instance = this;
	Log::Init();

	ResourceManager::Get().SetRootResourcesPath("../App/Assets/Images/");
	m_ImGuiLayer.Init();
}

EngineApplication::~EngineApplication()
{
	UNSUBSCRIBE_WINDOW_EVENT(this, EngineApplication::Quit);

	if(m_Game->IsRunning())
		m_Game->ShutdownGame();

	delete m_Game;
	
	delete CC_Window;
	delete CC_RendererSystem;
	delete CC_EventSystem;

	ResourceManager::Get().UnloadResources();
	
	SDL_Quit();
}

void EngineApplication::Start()
{
}

void EngineApplication::Run()
{
	Start();
	
	while (m_IsRunning)
	{
		Time::Instance().Update();

		ProcessInput();
		Update();
		Render();
	}
}

void EngineApplication::ProcessInput() const
{
	CC_EventSystem->Update();
}

void EngineApplication::Update()
{
	if(m_Game->IsRunning())
		m_Game->UpdateGame(Time::Instance().DeltaTime());

	CC_RendererSystem->Update();

	m_ImGuiLayer.Update();
}

void EngineApplication::Render() 
{
	m_ImGuiLayer.Render();
	CC_RendererSystem->Render();
}


void EngineApplication::Quit(const CC_Event<CC_WindowEventType>& Event)
{
	m_IsRunning = false;
}
