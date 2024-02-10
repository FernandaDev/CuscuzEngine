#include <MLE.h>
#include "Application.h"

#include "Core/Time.h"

void Application::Start()
{
    EngineApplication::Start();
    ResourceManager::Instance().SetRootResourcesPath("../App/Assets/Images/");
    
    CC_RendererSystem->CreateSprite("Floor1.png", 250, 400);
    CC_RendererSystem->CreateSprite("Floor2.png", 600, 230);
    CC_RendererSystem->CreateSprite("Floor3.png", 420,  300, 2 , 2);

    m_Game->StartGame();
}

void Application::Update()
{
    EngineApplication::Update();

    if(m_Game->IsRunning())
        m_Game->UpdateGame(Time::Instance().DeltaTime());
}