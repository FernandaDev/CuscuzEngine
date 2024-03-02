#include "pch.h"
#include "AppImGuiLayer.h"
#include "EventSystem.h"
#include "imgui.h"
#include "GUI/imgui_impl_sdl.h"
#include "GUI/imgui_impl_sdlrenderer.h"
#include "Core/EngineApplication.h"
#include "Utils/Log.h"
#include "Game.h"
#include "Components/Animation2DComponent.h"
#include "Components/SpriteComponent.h"
#include "World/Actor.h"
#include "World/World.h"

AppImGuiLayer::AppImGuiLayer(const Window& Window, SDL_Renderer* Renderer) :
m_Renderer(Renderer)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForSDLRenderer(Window.GetWindow(), Renderer);
    ImGui_ImplSDLRenderer_Init(Renderer);
}

AppImGuiLayer::~AppImGuiLayer()
{
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void AppImGuiLayer::Start(const std::shared_ptr<Game>& Game)
{
    m_Game = Game;
    m_ShowMainWindow = true;
    EngineApplication::Get().CC_EventSystem->GetSDLEventDelegate()
                            .Add(this, &AppImGuiLayer::OnSDLEvent);
}

void AppImGuiLayer::Update()
{
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    
    if(m_ShowMainWindow)
        ShowMainWindow();
}

void AppImGuiLayer::ShowMainWindow()
{
    ImGui::Begin("World", &m_ShowMainWindow);
    
    const std::shared_ptr<Game> game = m_Game.lock();

     {
         const bool showingActorCreation = ImGui::CollapsingHeader("Actor Creation");
         ActorCreation(game, showingActorCreation);
     }
    
     {
         const bool showingActors = ImGui::CollapsingHeader("Actors List");
         ShowAllActors(game, showingActors);
     }
    
    ImGui::End();
}

void AppImGuiLayer::ActorCreation(const std::shared_ptr<Game>& Game, bool Showing) const
{
    if(!Game || !Showing)
        return;
    
    ImGui::BeginGroup();

    static glm::i32vec2 pos(0,0);
    ImGui::InputInt2("Position", &pos.x);


    static std::vector<Component*> components;
    ImGui::Spacing();
    ImGui::Text("SpriteComponent");
    ImGui::SameLine();
    if(ImGui::Button("Add"))
        components.emplace_back(new SpriteComponent());
    ImGui::Text("Animation2DComponent");
    ImGui::SameLine();
    if(ImGui::Button("Add2"))
        components.emplace_back(new Animation2DComponent(1));

    ImGui::BeginListBox("Components List", ImVec2(200, 50));
    if(!components.empty())
    {
        for (const auto& component : components)
            ImGui::Text(component->GetName().data());
    }
    ImGui::EndListBox();
    
    if(ImGui::Button("Create Actor"))
    {
        const auto newName = "Actor" + std::to_string(Game->m_World->GetActorsCount());
        const auto newActor = Game->CreateNewActor(newName, pos.x, pos.y);

        for (const auto& c : components)
            newActor->AddComponent(c);
    }

    ImGui::EndGroup();
}

void AppImGuiLayer::ShowAllActors(const std::shared_ptr<Game>& Game, bool Showing) const
{
    if(!Game || !Showing)
        return;
    
    const auto allActors = Game->m_World->GetAllActors();

    for (size_t i = 0; i < allActors.size(); ++i)
    {
        if(const auto actor = allActors[i].get())
            ShowActor(actor, static_cast<int>(i));
    }
}

void AppImGuiLayer::ShowActor(Actor* TheActor, int Index) const
{
    ImGui::BeginGroup();
            
    ImGui::Text(TheActor->GetName().c_str());
    ImGui::SameLine();
    if(ImGui::Button("Destroy"))
        TheActor->Destroy();

    ImGui::Spacing();
    ImGui::TextColored(ImVec4(0.f,.5f,1.f,1.f),"Components");
    const auto name = std::to_string(Index);
    ImGui::BeginListBox(name.c_str(), ImVec2(200, 50));
    for (const auto& component : TheActor->m_Components)
    {
         ImGui::Text(component->GetName().data());
    }
    ImGui::EndListBox();
    ImGui::Spacing();
    
    ImGui::Text("Position: ");
    ImGui::SameLine();
    ImGui::Text("X: %f ", TheActor->GetPosition().x);
    ImGui::SameLine();
    ImGui::Text("Y: %f ", TheActor->GetPosition().y);

    ImGui::Text("Rotation: %f", TheActor->GetRotation());
    ImGui::Text("Scale: %f", TheActor->GetScale());
            
    ImGui::EndGroup();
    ImGui::Separator();
}

void AppImGuiLayer::Render()
{
    const ImGuiIO io = ImGui::GetIO();
    ImGui::Render();
    SDL_RenderSetScale(m_Renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
}

void AppImGuiLayer::OnSDLEvent(const SDL_Event& Event)
{
    ImGui_ImplSDL2_ProcessEvent(&Event);
}

#if 0 //example code
bool ShowDemoWindow = true;
bool ShowAnotherWindow = false;
ImVec4 ClearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

static void ExampleCode()
{
    if (ShowDemoWindow)
        ImGui::ShowDemoWindow(&ShowDemoWindow);

    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text."); // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &ShowDemoWindow); // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &ShowAnotherWindow);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f); // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&ClearColor); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))
            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);
        ImGui::End();
    }

    // 3. Show another simple window.
    if (ShowAnotherWindow)
    {
        ImGui::Begin("Another Window", &ShowAnotherWindow);
        // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            ShowAnotherWindow = false;
        ImGui::End();
    }
}
#endif

