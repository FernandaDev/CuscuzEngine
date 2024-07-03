#pragma once

#include "CC_Application.h"

extern CC_Application* CreateApplication();

int main(int argc, char* argv[])
{
    const auto app = CreateApplication();

    app->Run();

    delete app;
    
    return 0;
}