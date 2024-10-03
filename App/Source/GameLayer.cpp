#include "GameLayer.h"

#include "Components/Animation2DComponent.h"
#include "Core/KeyCodes.h"
#include "ImGui/imgui.h"
#include "Events/KeyEvents.h"
#include "World/Actor.h"
#include "World/World.h"

void GameLayer::OnAttach()
{
    Layer::OnAttach();

    World world;
    
    auto actor = new Actor(&world , "MyName", glm::vec2(0,0));
    actor->AddComponent<SpriteComponent>();

    auto comp = actor->GetComponent<SpriteComponent>();

    actor->RemoveComponent<SpriteComponent>();
}

void GameLayer::OnDetach()
{
    Layer::OnDetach();
}

void GameLayer::OnEvent(CC_Event& event)
{
    Layer::OnEvent(event);

    CC_EventSingleDispatcher eventDispatcher(event);
    eventDispatcher.Dispatch<CC_KeyDownEvent>(BIND_FUNCTION(this, GameLayer::ToggleWindow));
}

bool GameLayer::ToggleWindow(const CC_KeyDownEvent& event)
{
    if(event.GetKeyCode() == CC_KeyCode::F1)
        m_ShowWorldWindow = !m_ShowWorldWindow;
    
    return false;
}

void GameLayer::OnImGuiRender()
{
    Layer::OnImGuiRender();

    if(m_ShowWorldWindow)
        ShowWorldWindow();
}

void GameLayer::ShowWorldWindow()
{
    ImGui::Begin("World", &m_ShowWorldWindow);
    //
    // {
    //     const bool showingActorCreation = ImGui::CollapsingHeader("Actor Creation");
    //     ActorCreation(showingActorCreation);
    // }
    //
    // {
    //     const bool showingActors = ImGui::CollapsingHeader("Actors List");
    //     ShowAllActors(showingActors);
    // }
    
    ImGui::End();
}

void GameLayer::ActorCreation(bool showing) const
{
    // if(!showing)
    //     return;
    //
    // ImGui::BeginGroup();
    //
    // static glm::i32vec2 pos(0,0);
    // ImGui::InputInt2("Position", &pos.x);
    //
    // static std::vector<Component*> components;
    // ImGui::Spacing();
    // ImGui::Text("SpriteComponent");
    // ImGui::SameLine();
    // if(ImGui::Button("Add"))
    //     components.emplace_back(new SpriteComponent());
    // ImGui::Text("Animation2DComponent");
    // ImGui::SameLine();
    // if(ImGui::Button("Add2"))
    //     components.emplace_back(new Animation2DComponent(1));
    //
    // ImGui::BeginListBox("Components List", ImVec2(200, 50));
    // if(!components.empty())
    // {
    //     for (const auto& component : components)
    //         ImGui::Text(component->GetName().data());
    // }
    // ImGui::EndListBox();
    //
    // if(ImGui::Button("Create Actor"))
    // {
    //     const auto newName = "Actor" + std::to_string(m_AppGame->m_World.GetActorsCount());
    //     const auto newActor = m_AppGame->CreateNewActor(newName, pos.x, pos.y);
    //
    //     for (const auto& c : components)
    //         newActor->AddComponent(c);
    // }

    ImGui::EndGroup();
}

void GameLayer::ShowAllActors(bool showing) const
{
    // if(!showing)
    //     return;
    //
    // const auto allActors = m_AppGame->m_World.GetAllActors();
    //
    // for (size_t i = 0; i < allActors.size(); ++i)
    // {
    //     if(const auto actor = allActors[i].get())
    //         ShowActor(actor, static_cast<int>(i));
    // }
}

void GameLayer::ShowActor(Actor* actor, int index) const
{
    // ImGui::BeginGroup();
    //         
    // ImGui::Text(actor->GetName().c_str());
    // ImGui::SameLine();
    // if(ImGui::Button("Destroy"))
    //     actor->Destroy();
    //
    // ImGui::Spacing();
    // ShowActorComponents(actor, index);
    // ImGui::Spacing();
    //
    // ImGui::Text("Position: ");
    // ImGui::SameLine();
    // ImGui::Text("X: %f ", actor->GetPosition().x);
    // ImGui::SameLine();
    // ImGui::Text("Y: %f ", actor->GetPosition().y);
    //
    // ImGui::Text("Rotation: %f", actor->GetRotation());
    // ImGui::Text("Scale: %f", actor->GetScale());
    //         
    // ImGui::EndGroup();
    // ImGui::Separator();
}

void GameLayer::ShowActorComponents(Actor* actor, int index) const
{
    // ImGui::TextColored(ImVec4(0.f,.5f,1.f,1.f),"Components");
    //
    // const auto name = std::to_string(index);
    // ImGui::BeginListBox(name.c_str(), ImVec2(300, 50));
    // for (const auto& component : actor->GetComponents())
    // {
    //     ImGui::Text(component->GetName().data());
    // }
    // ImGui::EndListBox();
}
