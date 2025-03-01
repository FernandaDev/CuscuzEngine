#include <Cuscuz/Core/EntryPoint.h>
#include "GameLayer.h"

class GameApp : public Cuscuz::Engine
{
public:
    GameApp()
    {
        PushLayer(std::make_shared<GameLayer>());
    }

    ~GameApp() override = default;
};


Cuscuz::Engine* Cuscuz::CreateApplication() { return new GameApp(); }