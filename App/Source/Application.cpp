#include "Application.h"
#include "ResourceManager.h"

void Application::Start()
{
    EngineApplication::Start();
    ResourceManager::Instance().SetRootResourcesPath("../App/Assets/Images/");
    
    m_RendererSystem->CreateSprite("Floor1.png", 250, 400);
    m_RendererSystem->CreateSprite("Floor2.png", 600, 230);
    m_RendererSystem->CreateSprite("Floor3.png", 420,  300, 2 , 2);
}

void Application::Update()
{
    EngineApplication::Update();
}
