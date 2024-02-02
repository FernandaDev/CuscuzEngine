#pragma once

#include "EngineApplication.h"
#include "Events/KeyEvents.h"

class Application : public EngineApplication
{    
public:
    Application() = default;
    ~Application() override = default;

    void Start() override;
    void Update() override;

    void OnKeyDown(const CC_Event<CC_KeyEventType>& Event);
};
