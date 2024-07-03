#pragma once

#include "Core/CC_Application.h"

class AppGame;

class Application : public CC_Application
{
    std::shared_ptr<AppGame> m_AppGame;

public:
    Application();
    ~Application() override = default;

    void Start() override;
protected:
    void Render() override;
};
