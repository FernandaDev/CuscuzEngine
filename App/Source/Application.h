#pragma once

#include "CC_Engine.h"

class AppGame;

class Application : public CC_Engine
{
    std::shared_ptr<AppGame> m_AppGame;

public:
    Application();
    ~Application() override = default;

    void Start() override;
protected:
    void Render() override;
};
