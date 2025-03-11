#include "EditorLayer.h"

#include "Cuscuz/core/Input.h"
#include "Cuscuz/Utils/Instrumentor.h"
#include "ext/matrix_transform.hpp"
#include "ImGui/imgui.h"
#include "Utils/ImGuiHelper_ActorCreation.h"
#include "Utils/ImGuiHelper_Settings.h"
#include "Utils/ImGuiHelper_World.h"

struct Tile
{
    glm::mat4 Transform;
    Cuscuz::CC_AssetRef<Cuscuz::SubTexture2D> SubTexture;

    Tile(const Cuscuz::CC_AssetRef<Cuscuz::SubTexture2D>& subTexture, glm::mat4 transform):
    Transform(transform), SubTexture(subTexture) { }

    const glm::vec3& GetPos() { return { Transform[3] }; }
};

std::vector<Tile> gTiles;

EditorLayer::EditorLayer() :
m_Camera(std::make_unique<Cuscuz::OrthoCameraController>(static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT), true)),
m_EditorWorld(std::make_unique<Cuscuz::World>()),
m_EditorScene(std::make_unique<Cuscuz::Scene>()),
m_ActorSprite(std::make_shared<Cuscuz::Sprite>()),
m_ShowWorldWindow(true), m_ShowTimeStatsOverlay(true)
{  }

void EditorLayer::OnAttach()
{
    CC_PROFILE_FUNCTION();
    
    m_MainActor = &m_EditorWorld->CreateActor("Fer", glm::vec3(0, 0, 0), 1.f);
    m_MainActor->AddComponent<Cuscuz::CircleDetectionComponent>(48.f);
    auto& actorSprite = m_MainActor->AddComponent<Cuscuz::SpriteRenderer>();
    
    m_ActorTexture = Cuscuz::Texture2D::Create("Assets/Images/player.png");
    m_ActorSprite->SetTexture(m_ActorTexture);
    
    actorSprite.SetSprite(m_ActorSprite);

    m_Spritesheet = Cuscuz::Texture2D::Create("Assets/Images/Map_SpriteSheet.png");
    m_MapTiles[0] = Cuscuz::SubTexture2D::CreateFromCoords(m_Spritesheet, {5, 29}, {16,16}, {1,1}, 1.f);
    m_MapTiles[1] = Cuscuz::SubTexture2D::CreateFromCoords(m_Spritesheet, {3, 29}, {16,16}, {1,1}, 1.f);
    m_MapTiles[2] = Cuscuz::SubTexture2D::CreateFromCoords(m_Spritesheet, {6, 29}, {16,16}, {1,1}, 1.f);

    const glm::ivec2& gridSize = {25,25};

    gTiles.clear();
    gTiles.reserve(gridSize.x * gridSize.y);
    
    Random& random = Random::Get();
    float halfGridX = gridSize.x * 0.5f;
    float halfGridY = gridSize.y * 0.5f;
    
    for (int x = 0; x < gridSize.x; ++x)
    {
        for (int y = 0; y < gridSize.y; ++y)
        {
            auto pos = glm::vec3(x - halfGridX , y - halfGridY, -0.1f);
            //LOG_INFO("Pos: {0}, {1}", pos.x, pos.y);
            const auto randomIndex = random.GetRandomNumber(0, m_MapTiles.size() - 1);
            std::shared_ptr<Cuscuz::SubTexture2D>& tile = m_MapTiles[randomIndex];
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos);
            gTiles.emplace_back(tile, transform);
        }
    }
}

void EditorLayer::OnUpdate(float deltaTime)
{
    CC_PROFILE_FUNCTION();
    
    m_Camera->OnUpdate(deltaTime);
    
    m_EditorWorld->Update(deltaTime); // Game thread
    MoveActor(deltaTime);

    Cuscuz::Renderer2D::ResetStats();
    Cuscuz::RenderCommand::SetClearColor({0.6f, 0.6f, 0.6f, 1.0f});
    Cuscuz::RenderCommand::Clear();

    Cuscuz::Renderer2D::BeginScene(m_Camera->GetCamera());
    
    for (size_t i = 0; i < gTiles.size(); i++)
    {
        Cuscuz::Renderer2D::DrawQuad(gTiles[i].Transform, {1.f,1.f,1.f,1.f}, gTiles[i].SubTexture);
    }
    
    Cuscuz::Renderer2D::EndScene();
    
    m_EditorScene->OnRender(m_Camera->GetCamera()); // Render Thread
}

void EditorLayer::MoveActor(float deltaTime)
{
    auto pos = m_MainActor->GetTransform().GetPosition();
    
    if(Cuscuz::Input::IsKeyPressed(Cuscuz::CC_KEYCODE_W))
        pos.y += MoveSpeed * deltaTime;
    if(Cuscuz::Input::IsKeyPressed(Cuscuz::CC_KEYCODE_S))
        pos.y -= MoveSpeed * deltaTime;
    if(Cuscuz::Input::IsKeyPressed(Cuscuz::CC_KEYCODE_A))
        pos.x -= MoveSpeed * deltaTime;
    if(Cuscuz::Input::IsKeyPressed(Cuscuz::CC_KEYCODE_D))
        pos.x += MoveSpeed * deltaTime;
    
    m_MainActor->GetTransform().SetPosition(pos);
}

void EditorLayer::OnImGuiRender()
{
    if (m_ShowWorldWindow)
        ShowWorldWindow();

    if (m_ShowTimeStatsOverlay)
        ImGuiHelper::ShowTimeOverlay(m_ShowTimeStatsOverlay);
}

void EditorLayer::OnEvent(Cuscuz::CuscuzEvent& event)
{
    Layer::OnEvent(event);

    m_Camera->OnEvent(event);
    // Cuscuz::CC_EventSingleDispatcher eventDispatcher(event);
    // eventDispatcher.Dispatch<CC_KeyDownEvent>(BIND_FUNCTION(this, EditorLayer::ToggleWindow));
}

bool EditorLayer::ToggleWindow(const CC_KeyDownEvent& event)
{
    // if (event.GetKeyCode() == Cuscuz::CC_KeyCode::F1)
    //     m_ShowWorldWindow = !m_ShowWorldWindow;

    return false;
}

void EditorLayer::ShowWorldWindow()
{
    ImGui::Begin("World", &m_ShowWorldWindow, ImGuiWindowFlags_MenuBar);

    static bool showActorCreation = false;
    static bool showCameraWindow = false;
    static bool showTimeStatsWindow = false;
    static bool showRendererStatsWindow = true;

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Tools"))
        {
            ImGui::MenuItem("Create New Actor", NULL, &showActorCreation);

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Camera"))
        {
            ImGui::MenuItem("Settings", NULL, &showCameraWindow);

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Stats"))
        {
            ImGui::MenuItem("Time", NULL, &showTimeStatsWindow);
            ImGui::MenuItem("Renderer", NULL, &showRendererStatsWindow);

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    // if (showActorCreation)
    //     ImGuiHelper::ShowActorCreation(showActorCreation, m_World);

    if (showCameraWindow)
        ImGuiHelper::ShowCameraWindow(showCameraWindow);

    if (showTimeStatsWindow)
        ImGuiHelper::ShowTimeStatsWindow(showTimeStatsWindow, m_ShowTimeStatsOverlay);

    if (showRendererStatsWindow)
        ImGuiHelper::ShowRendererStatsWindow(showRendererStatsWindow);

    const bool showingActors = ImGui::CollapsingHeader("Hierarchy", ImGuiTreeNodeFlags_DefaultOpen);
    //ImGuiHelper::ShowAllActors(showingActors, m_World);

    ImGui::End();
}
