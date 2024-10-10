#pragma once

#include "CC_Engine.h"

extern CC_Engine* CreateApplication();

inline int main(int argc, char* argv[])
{
    const auto app = CreateApplication();

    app->Run();

    delete app;
    
    return 0;
}