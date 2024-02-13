#include <CC_Engine.h>

#include "Application.h"
#include "Core/Time.h"

void Application::Start()
{
    EngineApplication::Start();
    ResourceManager::Instance().SetRootResourcesPath("../App/Assets/Images/");

    m_Game->StartGame();
}

void Application::Update()
{
    EngineApplication::Update();

    if(m_Game->IsRunning())
        m_Game->UpdateGame(Time::Instance().DeltaTime());
}