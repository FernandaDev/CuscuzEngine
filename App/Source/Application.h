#pragma once

#include "EngineApplication.h"

class Application : public EngineApplication
{    
public:
    Application() = default;
    ~Application() override = default;

    void Start() override;
    void Update() override;
};
