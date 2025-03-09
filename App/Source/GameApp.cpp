#include <Cuscuz/Core/EntryPoint.h>

#include "GameLayer.h"
#include "Editor/EditorLayer.h"

class GameApp : public Cuscuz::Engine
{
public:
    GameApp()
    {
        PushLayer(std::make_shared<EditorLayer>());
    }

    ~GameApp() override = default;
};


Cuscuz::Engine* Cuscuz::CreateApplication() { return new GameApp(); }