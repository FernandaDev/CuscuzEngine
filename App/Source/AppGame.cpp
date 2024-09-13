#include <..\..\CuscuzEngine\Source\CC_Core.h>
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

    // BACKGROUND
    Actor* bg = CreateNewActor("Background",SCREEN_WIDTH/2,SCREEN_HEIGHT/2);

    const auto bgSprite = ResourceManager::Get().CreateSprite("BG.png", renderer);

    const auto backgroundSpriteComponent = new SpriteComponent(-999);
    backgroundSpriteComponent->SetSprite(bgSprite);

    bg->AddComponent<SpriteComponent>(backgroundSpriteComponent);

    // MOVING CHARACTER
    Actor* actorA = CreateNewActor("ActorA", 1030, 500);

    const auto animationComponent = new Animation2DComponent(4);
    actorA->AddComponent<Animation2DComponent>(animationComponent);

    const auto simpleMoveComponent = new Simple2DMovementComponent(-20, 0);
    actorA->AddComponent<Simple2DMovementComponent>(simpleMoveComponent);
    
    const auto sprite = ResourceManager::Get().CreateSprite("player_tilesheet.png", renderer);
    animationComponent->SetSprite(sprite);

    //CONTROLLED CHARACTER
    Hero* hero = new Hero(&m_World, "hero", glm::vec2(400,500));
    
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