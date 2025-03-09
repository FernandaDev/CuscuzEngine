#pragma once

#include "Engine.h"

extern Cuscuz::Engine* Cuscuz::CreateApplication();

int main(int argc, char* argv[])
{
    const auto app = Cuscuz::CreateApplication();

    app->Run();

    delete app;
    
    return 0;
}