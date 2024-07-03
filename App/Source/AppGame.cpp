#include <CC_Engine.h>
#include "AppGame.h"

#include "Utils/Log.h"
#include "Application.h"
#include "Hero.h"
#include "World/Actor.h"
#include "Components/SpriteComponent.h"
#include "Components/Animation2DComponent.h"
#include "Components/Simple2DMovementComponent.h"

void AppGame::OnGameBegin()
{
    CC_Game::OnGameBegin();

    const auto renderer = Application::Get().CC_RendererSystem->GetRenderer();

    Actor* actorA = CreateNewActor("ActorA", 230, 400);

    const auto animationComponent = new Animation2DComponent(4);
    actorA->AddComponent<Animation2DComponent>(animationComponent);

    const auto simpleMoveComponent = new Simple2DMovementComponent(10, 0);
    actorA->AddComponent<Simple2DMovementComponent>(simpleMoveComponent);
    
    const auto sprite = ResourceManager::Get().CreateSprite("player_tilesheet.png", renderer);
    animationComponent->SetSprite(sprite);
    
    Hero* hero = new Hero(&m_World, "hero", glm::vec2(200,200));
    
    const auto spriteComponent2 = new SpriteComponent( 10);
    hero->AddComponent<SpriteComponent>(spriteComponent2);
    
    const auto sprite2 = ResourceManager::Get().CreateSprite("soldier.png", renderer);
    spriteComponent2->SetSprite(sprite2);
}

void AppGame::OnGameEnd()
{
    CC_Game::OnGameEnd();
}

void AppGame::UpdateGame(float deltaTime)
{
    CC_Game::UpdateGame(deltaTime);
}

Actor* AppGame::CreateNewActor(const std::string& name, int x, int y)
{
    return new Actor(&m_World, name, glm::vec2(x,y));
}