#include <CC_Engine.h>
#include <Core/EntryPoint.h>

#include "Application.h"
#include "AppGame.h"

EngineApplication* CreateApplication()
{
    return new Application();
}

Application::Application() : EngineApplication(new AppGame())
{}

void Application::Start()
{
    EngineApplication::Start();
}

void Application::Render()
{
    EngineApplication::Render();
}
