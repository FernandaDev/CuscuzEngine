#include "pch.h"
#include "GameLayer.h"

#include "Components/SpriteComponent.h"
#include "Core/KeyCodes.h"
#include "ImGui/imgui.h"
#include "Events/KeyEvents.h"
#include "Utils/ImGuiHelper_World.h"
#include "World/Actor.h"

struct my_struct
{
    int value = 0;
};


GameLayer::GameLayer() : m_World(std::make_unique<World>()),
m_ActorTexture(std::make_shared<OpenGLTexture>()), m_ActorSprite(std::make_shared<Sprite>())
{}

void GameLayer::OnAttach()
{
    Layer::OnAttach();

    auto& actor = m_World->CreateActor("Fer", glm::vec2(1, 1), 1.f);
    auto& actorSprite = actor.AddComponent<SpriteComponent>();

    m_ActorTexture->Load("Assets/Images/player.png");
    m_ActorSprite->SetTexture(m_ActorTexture);

    actorSprite.SetSprite(m_ActorSprite);
}

void GameLayer::OnDetach()
{
    Layer::OnDetach();
}

void GameLayer::OnUpdate(float deltaTime)
{
    Layer::OnUpdate(deltaTime);

    m_World->Update(deltaTime);
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
    // {
    //     const bool showingActors = ImGui::CollapsingHeader("Actors List", ImGuiTreeNodeFlags_DefaultOpen);
    //     ShowAllActors(showingActors, m_World.get());
    // }
    
    ImGui::End();
}