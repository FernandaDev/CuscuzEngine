#include <CC_Engine.h>
#include <Core/EntryPoint.h>

#include "Application.h"
#include "AppGame.h"
#include "AppGameLayer.h"

EngineApplication* CreateApplication()
{
    return new Application();
}

Application::Application() : m_AppGame(new AppGame)
{
    CreateGame(m_AppGame);
}

void Application::Start()
{
    EngineApplication::Start();

    PushOverlay(new AppGameLayer(m_AppGame));
}

void Application::Render()
{
    EngineApplication::Render();
}
