#include <Core/EntryPoint.h>

#include "GameLayer.h"

class GameApp : public CC_Engine
{
public:
    GameApp()
    {
        PushLayer(std::make_shared<GameLayer>());
    }

    ~GameApp() override = default;
};


CC_Engine* CreateApplication() { return new GameApp(); }