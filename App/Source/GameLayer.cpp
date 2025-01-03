#include "pch.h"
#include "GameLayer.h"

#include "Components/CircleDetectionComponent.h"
#include "Components/Simple2DMovementComponent.h"
#include "Components/SpriteRenderer.h"
#include "Core/CC_Engine.h"
#include "Core/Input.h"
#include "Core/KeyCodes.h"
#include "World/Actor.h"

GameLayer::GameLayer() :
m_ActorSprite(std::make_shared<Sprite>()),
m_EnemySprite(std::make_shared<Sprite>())
{
    m_World = CC_Engine::Get().CC_World.get();
}

void GameLayer::OnAttach()
{
    CC_ASSERT(m_World, "The World instance is null!");
    
    m_MainActor = &m_World->CreateActor("Fer", glm::vec3(0, 0, 0));
    m_MainActor->AddComponent<CircleDetectionComponent>(48.f);
    auto& actorSprite = m_MainActor->AddComponent<SpriteRenderer>();

    const auto texture = Texture2D::Create("Assets/Images/player.png");
    m_ActorSprite->SetTexture(texture);

    actorSprite.SetSprite(m_ActorSprite);

    m_EnemyActor = &m_World->CreateActor("Enemy", glm::vec3(150, 0, 0));
    auto& enemySprite = m_EnemyActor->AddComponent<SpriteRenderer>();
    auto enemyTexture = Texture2D::Create("Assets/Images/adventurer.png");
    m_EnemySprite->SetTexture(enemyTexture);
    enemySprite.SetSprite(m_EnemySprite);
    
    //m_EnemyActor->AddComponent<CircleDetectionComponent>(48.f);
    //m_EnemyActor->AddComponent<Simple2DMovementComponent>();
}

void GameLayer::OnDetach()
{}

static float MoveSpeed = 100.0f;

void GameLayer::OnUpdate(float deltaTime)
{
    CC_ASSERT(m_World, "The World instance is null!");
    
    m_World->Update(deltaTime);

    auto pos = m_MainActor->GetTransform().GetPosition();

    if(Input::IsKeyPressed(CC_KEYCODE_W))
        pos.y += MoveSpeed * deltaTime;
    if(Input::IsKeyPressed(CC_KEYCODE_S))
        pos.y -= MoveSpeed * deltaTime;
    if(Input::IsKeyPressed(CC_KEYCODE_A))
        pos.x -= MoveSpeed * deltaTime;
    if(Input::IsKeyPressed(CC_KEYCODE_D))
        pos.x += MoveSpeed * deltaTime;

    m_MainActor->GetTransform().SetPosition(pos);
}

void GameLayer::OnEvent(CC_Event& event)
{
}

void GameLayer::OnImGuiRender()
{
}
