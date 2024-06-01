#pragma once

#include "Core/EngineApplication.h"

class Application : public EngineApplication
{
public:
    Application();
    ~Application() override = default;

    void Start() override;
    void Update() override;
protected:
    void Render() override;
};
