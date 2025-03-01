#include "pch.h"
#include "GameLayer.h"

#include "Cuscuz/Components/CircleDetectionComponent.h"
#include "Cuscuz/Components/Simple2DMovementComponent.h"
#include "Cuscuz/Components/SpriteRenderer.h"
#include "Cuscuz/Core/Engine.h"
#include "Cuscuz/Core/Input.h"
#include "Cuscuz/Core/KeyCodes.h"
#include "Cuscuz/Render/Texture.h"
#include "Cuscuz/World/Actor.h"
#include "Cuscuz/Utils/Random.h"


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

GameLayer::GameLayer() : m_ActorSprite(std::make_shared<Cuscuz::Sprite>())
{
    m_World = Cuscuz::Engine::Get().CC_World.get();
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

    DrawGrid({10, 10}, m_World);
}

void GameLayer::OnDetach()
{}

static float MoveSpeed = 10.0f;

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

void GameLayer::OnEvent(Cuscuz::CC_Event& event)
{
}

void GameLayer::OnImGuiRender()
{
}
