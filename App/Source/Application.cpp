#include <..\..\CuscuzEngine\Source\CC_Core.h>
#include <Core/EntryPoint.h>

#include "Application.h"
#include "AppGame.h"
#include "AppGameLayer.h"

CC_Engine* CreateApplication()
{
    return new Application();
}

Application::Application() : m_AppGame(std::make_shared<AppGame>())
{
    CreateGame(m_AppGame);
}

void Application::Start()
{
    CC_Engine::Start();

    PushOverlay(std::make_shared<AppGameLayer>(m_AppGame));
}

void Application::Render()
{
    CC_Engine::Render();
}
