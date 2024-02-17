#pragma once

#include "EngineApplication.h"

extern EngineApplication* CreateApplication();

int main(int argc, char* argv[])
{
    const auto app = CreateApplication();

    app->Run();

    delete app;
    
    return 0;
}