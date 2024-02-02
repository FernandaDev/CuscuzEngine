#include <MLE.h>
#include "Application.h"

void Application::Start()
{
    EngineApplication::Start();
    ResourceManager::Instance().SetRootResourcesPath("../App/Assets/Images/");
    
    m_RendererSystem->CreateSprite("Floor1.png", 250, 400);
    m_RendererSystem->CreateSprite("Floor2.png", 600, 230);
    m_RendererSystem->CreateSprite("Floor3.png", 420,  300, 2 , 2);
    
    SUBSCRIBE_KEY_EVENT(CC_KeyEventType::Down, this, Application::OnKeyDown);
}

static bool subscribed = false;

void Application::Update()
{
    EngineApplication::Update();

    if(Input::IsKeyPressed(CC_KeyCode::Alpha2))
    {
        LOG_INFO("Unsubscribed from event...");
        UNSUBSCRIBE_KEY_EVENT(this, Application::OnKeyDown);
        subscribed = false;
    }

    if(Input::IsKeyPressed(CC_KeyCode::Alpha1) && !subscribed)
    {
        LOG_INFO("Subscribed on event...");
        SUBSCRIBE_KEY_EVENT(CC_KeyEventType::Down, this, Application::OnKeyDown);
        subscribed = true;
    }
}

void Application::OnKeyDown(const CC_Event<CC_KeyEventType>& Event)
{
    auto e = Event.ToType<CC_KeyDownEvent>();

    if(e.GetKeyCode() == CC_KeyCode::Space)
    {
        LOG_INFO(Event.ToString());
    }
}
