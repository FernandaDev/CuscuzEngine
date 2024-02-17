#include <CC_Engine.h>
#include <Core/EntryPoint.h>

#include "Application.h"
#include "Core/Time.h"

EngineApplication* CreateApplication() { return new Application(); }

void Application::Start()
{
    EngineApplication::Start();
    ResourceManager::Get().SetRootResourcesPath("../App/Assets/Images/");

    m_Game->StartGame();
}

void Application::Update()
{
    EngineApplication::Update();

    if(m_Game->IsRunning())
        m_Game->UpdateGame(Time::Instance().DeltaTime());
}