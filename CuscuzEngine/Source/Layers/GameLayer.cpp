#include "pch.h"
#include "GameLayer.h"

#include "Core/Time.h"

GameLayer::GameLayer(CC_Game* Game) : Layer("Game Layer"),
m_Game(Game)
{}

void GameLayer::OnUpdate()
{
    Layer::OnUpdate();
    if(m_Game->IsRunning())
        m_Game->UpdateGame(Time::Instance().DeltaTime());
}
