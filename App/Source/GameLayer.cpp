#include "pch.h"
#include "GameLayer.h"

#include "Components/SpriteRenderer.h"
#include "Core/Input.h"
#include "Core/KeyCodes.h"
#include "ImGui/imgui.h"
#include "Events/KeyEvents.h"
#include "Utils/ImGuiHelper_World.h"

GameLayer::GameLayer() : m_World(std::make_unique<World>()),
m_ActorSprite(std::make_shared<Sprite>()), m_EnemySprite(std::make_shared<Sprite>())
{}

void GameLayer::OnAttach()
{
    Layer::OnAttach();

    m_MainActor = &m_World->CreateActor("Fer", glm::vec2(5, 4), 1.f);
    auto& actorSprite = m_MainActor->AddComponent<SpriteRenderer>();

    m_ActorTexture = std::make_shared<OpenGLTexture>("Assets/Images/player.png");
    m_ActorSprite->SetTexture(m_ActorTexture);

    actorSprite.SetSprite(m_ActorSprite);

    m_EnemyActor = &m_World->CreateActor("Enemy", glm::vec2(10, 4), 1.f);
    auto& enemySprite = m_EnemyActor->AddComponent<SpriteRenderer>();

    m_EnemyTexture = std::make_shared<OpenGLTexture>("Assets/Images/adventurer.png");
    m_EnemySprite->SetTexture(m_EnemyTexture);

    enemySprite.SetSprite(m_EnemySprite);
}

void GameLayer::OnDetach()
{
    Layer::OnDetach();
}

void GameLayer::OnUpdate(float deltaTime)
{
    Layer::OnUpdate(deltaTime);

    m_World->Update(deltaTime);

    auto pos = m_MainActor->GetTransform().GetPosition();

    if(Input::IsKeyPressed(CC_KEYCODE_W))
        pos.y += deltaTime;
    else if(Input::IsKeyPressed(CC_KEYCODE_S))
        pos.y -= deltaTime;
    else if(Input::IsKeyPressed(CC_KEYCODE_A))
        pos.x -= deltaTime;
    else if(Input::IsKeyPressed(CC_KEYCODE_D))
        pos.x += deltaTime;

    m_MainActor->GetTransform().SetPosition(pos);
}

void GameLayer::OnEvent(CC_Event& event)
{
    Layer::OnEvent(event);

    CC_EventSingleDispatcher eventDispatcher(event);
    eventDispatcher.Dispatch<CC_KeyDownEvent>(BIND_FUNCTION(this, GameLayer::ToggleWindow));
}

bool GameLayer::ToggleWindow(const CC_KeyDownEvent& event)
{
    if (event.GetKeyCode() == CC_KeyCode::F1)
        m_ShowWorldWindow = !m_ShowWorldWindow;

    return false;
}

void GameLayer::OnImGuiRender()
{
    Layer::OnImGuiRender();

    if (m_ShowWorldWindow)
        ShowWorldWindow();
}

void GameLayer::ShowWorldWindow()
{
    ImGui::Begin("World", &m_ShowWorldWindow);
    
    // {
    //     const bool showingActorCreation = ImGui::CollapsingHeader("Actor Creation", ImGuiTreeNodeFlags_DefaultOpen);
    //     ShowActorCreation(showingActorCreation, m_World.get());
    // }
    //
    {
        const bool showingActors = ImGui::CollapsingHeader("Actors List", ImGuiTreeNodeFlags_DefaultOpen);
        ImGuiHelper::ShowAllActors(showingActors, m_World.get());
    }
    
    ImGui::End();
}