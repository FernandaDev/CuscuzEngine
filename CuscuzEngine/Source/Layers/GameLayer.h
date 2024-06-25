#pragma once

#include "Layer.h"
#include "Core/CC_Game.h"

class GameLayer : public Layer
{
    CC_Game* m_Game;
    
public:
    GameLayer(CC_Game* Game);

    void OnUpdate() override;
};
