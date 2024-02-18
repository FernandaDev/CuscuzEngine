#include <CC_Engine.h>
#include <Core/EntryPoint.h>

#include "Application.h"
#include "Core/Time.h"

EngineApplication* CreateApplication() { return new Application(); }

void Application::Start()
{
    EngineApplication::Start();
    ResourceManager::Get().SetRootResourcesPath("../App/Assets/Images/");
    CC_GUILayer->Start(m_Game);
    
    m_Game->StartGame();
}

void Application::Update()
{
    EngineApplication::Update();
    CC_GUILayer->Update();

    if(m_Game->IsRunning())
        m_Game->UpdateGame(Time::Instance().DeltaTime());
}

void Application::Render() const
{
    CC_GUILayer->Render();
    EngineApplication::Render();
}
