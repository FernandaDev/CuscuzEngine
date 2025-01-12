#include "pch.h"
#include "GameLayer.h"

#include "Components/CircleDetectionComponent.h"
#include "Components/Simple2DMovementComponent.h"
#include "Components/SpriteRenderer.h"
#include "Core/CC_Engine.h"
#include "Core/Input.h"
#include "Core/KeyCodes.h"
#include "World/Actor.h"

static void DrawGrid(const glm::ivec2& gridSize, World* world)
{
    const float offset = 0.1f;
    for (int x = 0; x < gridSize.x; ++x)
    {
        for (int y = 0; y < gridSize.y; ++y)
        {
            auto pos = glm::vec3(x + x * offset, y + y * offset, 0.f);
            const auto actor = &world->CreateActor(std::format("tile_%i_%i", x, y), pos, 1.f);
            auto& sr = actor->AddComponent<SpriteRenderer>();
            sr.SetSprite(std::make_shared<Sprite>());
            sr.SetColor({ (float)x / (float)gridSize.x, (float)x / (float)gridSize.x, (float)y / (float)gridSize.y, 1.0f});
        }
    }
}

GameLayer::GameLayer()
{
    m_World = CC_Engine::Get().CC_World.get();
}

void GameLayer::OnAttach()
{
    CC_ASSERT(m_World, "The World instance is null!");
    
    // m_MainActor = &m_World->CreateActor("Fer", glm::vec3(0, 0, 0), 1.f);
    // m_MainActor->AddComponent<CircleDetectionComponent>(48.f);
    // auto& actorSprite = m_MainActor->AddComponent<SpriteRenderer>();
    //
    // const auto texture = Texture2D::Create("Assets/Images/player.png");
    // m_ActorSprite->SetTexture(texture);
    //
    // actorSprite.SetSprite(m_ActorSprite);

    DrawGrid({50, 50}, m_World);
}

void GameLayer::OnDetach()
{}

static float MoveSpeed = 100.0f;

void GameLayer::OnUpdate(float deltaTime)
{
    CC_ASSERT(m_World, "The World instance is null!");
    
    m_World->Update(deltaTime);

    // auto pos = m_MainActor->GetTransform().GetPosition();
    //
    // if(Input::IsKeyPressed(CC_KEYCODE_W))
    //     pos.y += MoveSpeed * deltaTime;
    // if(Input::IsKeyPressed(CC_KEYCODE_S))
    //     pos.y -= MoveSpeed * deltaTime;
    // if(Input::IsKeyPressed(CC_KEYCODE_A))
    //     pos.x -= MoveSpeed * deltaTime;
    // if(Input::IsKeyPressed(CC_KEYCODE_D))
    //     pos.x += MoveSpeed * deltaTime;
    //
    // m_MainActor->GetTransform().SetPosition(pos);
}

void GameLayer::OnEvent(CC_Event& event)
{
}

void GameLayer::OnImGuiRender()
{
}
