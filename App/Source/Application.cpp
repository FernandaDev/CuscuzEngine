#include <MLE.h>
#include "Application.h"

void Application::Start()
{
    EngineApplication::Start();
    ResourceManager::Instance().SetRootResourcesPath("../App/Assets/Images/");
    
    m_RendererSystem->CreateSprite("Floor1.png", 250, 400);
    m_RendererSystem->CreateSprite("Floor2.png", 600, 230);
    m_RendererSystem->CreateSprite("Floor3.png", 420,  300, 2 , 2);
    
    // ADD_KEY_EVENT_LISTENER(KeyEventType::Down, this, EventSystem::OnKeyDown);
    // ADD_KEY_EVENT_LISTENER(KeyEventType::Up, this, EventSystem::OnKeyUp);
    // ADD_MOUSE_EVENT_LISTENER(MouseEventType::ButtonDown, this, EventSystem::OnMouseButtonDown);
    // ADD_MOUSE_EVENT_LISTENER(MouseEventType::ButtonUp, this, EventSystem::OnMouseButtonUp);
}

void Application::Update()
{
    EngineApplication::Update();

    if(Input::IsKeyPressed(MLE_SCANCODE_SPACE))
    {
        LOG_INFO("Hi!!!");
    }

    if(Input::IsMousePressed(2))
    {
        LOG_INFO("Hey!!!");
    }
}
