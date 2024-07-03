#include <CC_Engine.h>
#include <Core/EntryPoint.h>

#include "Application.h"
#include "AppGame.h"
#include "AppGameLayer.h"

CC_Application* CreateApplication()
{
    return new Application();
}

Application::Application() : m_AppGame(std::make_shared<AppGame>())
{
    CreateGame(m_AppGame);
}

void Application::Start()
{
    CC_Application::Start();

    PushOverlay(new AppGameLayer(m_AppGame));
}

void Application::Render()
{
    CC_Application::Render();
}
