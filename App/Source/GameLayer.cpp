﻿#include "GameLayer.h"

static void DrawGrid(const glm::ivec2& gridSize, Cuscuz::World* world)
{
    Cuscuz::CC_AssetRef<Cuscuz::Texture2D> floors[3];
    
    floors[0] = Cuscuz::Texture2D::Create("Assets/Images/Floor1.png");
    floors[1] = Cuscuz::Texture2D::Create("Assets/Images/Floor2.png");
    floors[2] = Cuscuz::Texture2D::Create("Assets/Images/Floor3.png");

    Random& random = Random::Get();
    float halfGridX = gridSize.x * 0.5f;
    float halfGridY = gridSize.y * 0.5f;
    
    for (int x = 0; x < gridSize.x; ++x)
    {
        for (int y = 0; y < gridSize.y; ++y)
        {
            auto pos = glm::vec3(x - halfGridX , y - halfGridY, 0.f);
            const auto actor = &world->CreateActor(std::format("tile_{}_{}", x, y), pos, 1.f);
            auto& sr = actor->AddComponent<Cuscuz::SpriteRenderer>();
            auto sprite = std::make_shared<Cuscuz::Sprite>();

            auto randomIndex = random.GetRandomNumber(0, 2);
            
            auto texture = floors[randomIndex];
            sprite->SetTexture(texture);
            sr.SetSprite(sprite);
        }
    }
}

GameLayer::GameLayer() : m_World(std::make_unique<Cuscuz::World>()),
    m_ActorSprite(std::make_shared<Cuscuz::Sprite>())
{}

void GameLayer::OnAttach()
{
    CC_ASSERT(m_World, "The World instance is null!");

    m_MainActor = &m_World->CreateActor("Fer", glm::vec3(0, 0, 0), 1.f);
    m_MainActor->AddComponent<Cuscuz::CircleDetectionComponent>(48.f);
    auto& actorSprite = m_MainActor->AddComponent<Cuscuz::SpriteRenderer>();
    
    const auto texture = Cuscuz::Texture2D::Create("Assets/Images/player.png");
    m_ActorSprite->SetTexture(texture);
    
    actorSprite.SetSprite(m_ActorSprite);

    //DrawGrid({10, 10}, m_World);
}

void GameLayer::OnDetach()
{}

static float MoveSpeed = 10.0f;

void GameLayer::OnUpdate(float deltaTime)
{
    CC_ASSERT(m_World, "The World instance is null!");
    
    

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

void GameLayer::OnEvent(Cuscuz::CuscuzEvent& event)
{
}

void GameLayer::OnImGuiRender()
{
}
