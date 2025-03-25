#include "EditorLayer.h"

#include "Cuscuz/core/Input.h"
#include "Cuscuz/GUI/ImGuiLayer.h"
#include "Cuscuz/Utils/Instrumentor.h"
#include "ext/matrix_transform.hpp"
#include "ImGui/imgui.h"
#include "Utils\Editor_ActorCreation.h"
#include "Utils\Editor_Settings.h"
#include "Utils\Editor_World.h"

namespace Cuscuz
{
    static bool s_ShowHierarchy = true;
    static bool s_ShowInspector= true;
    static bool s_ShowTimeStatsOverlay = false;
    
    struct Tile
    {
        glm::mat4 Transform;
        CC_AssetRef<SubTexture2D> SubTexture;

        Tile(const CC_AssetRef<SubTexture2D>& subTexture, glm::mat4 transform):
        Transform(transform), SubTexture(subTexture) { }

        const glm::vec3& GetPos() { return { Transform[3] }; }
    };

    std::vector<Tile> gTiles;

    EditorLayer::EditorLayer() :
    m_Camera(std::make_unique<OrthoCameraController>(static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT), true)),
    m_EditorWorld(std::make_unique<World>()),
    m_EditorScene(std::make_unique<Scene>()),
    m_ActorSprite(std::make_shared<Sprite>())
    {  }

    void EditorLayer::OnAttach()
    {
        CC_PROFILE_FUNCTION();
    
        m_MainActor = &m_EditorWorld->CreateActor("Fer", glm::vec3(0, 0, 1.f), 1.f);
        m_MainActor->AddComponent<CircleDetectionComponent>(48.f);
        auto& actorSprite = m_MainActor->AddComponent<SpriteRenderer>();
        m_ActorTexture = Texture2D::Create("Assets/Images/player.png");
        m_ActorSprite->SetTexture(m_ActorTexture);
        actorSprite.SetSprite(m_ActorSprite);

        Actor* anotherActor = &m_EditorWorld->CreateActor("Another one", {2.0f, 0.f, 1.f}, 1.f);
        anotherActor->AddComponent<Simple2DMovementComponent>();
        SpriteRenderer& anotherSpriteComp = anotherActor->AddComponent<SpriteRenderer>();
        auto anotherTexture = Texture2D::Create("Assets/Images/soldier.png");
        CC_AssetRef<Sprite> anotherSprite = CreateAssetRef<Sprite>();
        anotherSprite->SetTexture(anotherTexture);
        anotherSpriteComp.SetSprite(anotherSprite);

        m_Spritesheet = Texture2D::Create("Assets/Images/Map_SpriteSheet.png");
        m_MapTiles[0] = SubTexture2D::CreateFromCoords(m_Spritesheet, {5, 29}, {16,16}, {1,1}, 1.f);
        m_MapTiles[1] = SubTexture2D::CreateFromCoords(m_Spritesheet, {3, 29}, {16,16}, {1,1}, 1.f);
        m_MapTiles[2] = SubTexture2D::CreateFromCoords(m_Spritesheet, {6, 29}, {16,16}, {1,1}, 1.f);

        FramebufferSpecification spec;
        spec.Width =  SCREEN_WIDTH;
        spec.Height = SCREEN_HEIGHT;
        m_Framebuffer = Framebuffer::Create(spec);
    
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
                std::shared_ptr<SubTexture2D>& tile = m_MapTiles[randomIndex];
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos);
                gTiles.emplace_back(tile, transform);
            }
        }
    }

    void EditorLayer::OnEvent(CuscuzEvent& event)
    {
        Layer::OnEvent(event);

        m_Camera->OnEvent(event);
        EventSingleDispatcher eventDispatcher(event);
        eventDispatcher.Dispatch<CC_KeyDownEvent>(BIND_FUNCTION(this, EditorLayer::OnKeyDownEvent));
    }

    void EditorLayer::OnUpdate(float deltaTime)
    {
        CC_PROFILE_FUNCTION();

        if (const FramebufferSpecification spec = m_Framebuffer->GetSpecification();
           m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
           (spec.Width != static_cast<uint32_t>(m_ViewportSize.x) || spec.Height != static_cast<uint32_t>(m_ViewportSize.y)))
        {
            m_Framebuffer->Resize(static_cast<uint32_t>(m_ViewportSize.x), static_cast<uint32_t>(m_ViewportSize.y));
            m_Camera->OnResize(m_ViewportSize.x, m_ViewportSize.y);
        }
        
        if(m_IsViewportFocused)
            m_Camera->OnUpdate(deltaTime);
    
        m_EditorWorld->Update(deltaTime); // Game thread
        MoveActor(deltaTime);

        Renderer2D::ResetStats();

        m_Framebuffer->Bind();
    
        RenderCommand::SetClearColor({0.6f, 0.6f, 0.6f, 1.0f});
        RenderCommand::Clear();

        Renderer2D::BeginScene(m_Camera->GetCamera());
    
        for (size_t i = 0; i < gTiles.size(); i++)
        {
            Renderer2D::DrawQuad(gTiles[i].Transform, {1.f,1.f,1.f,1.f}, gTiles[i].SubTexture);
        }
    
        Renderer2D::EndScene();
    
        m_EditorScene->OnRender(m_Camera->GetCamera()); // Render Thread

        m_Framebuffer->Unbind();
    }

    void EditorLayer::MoveActor(float deltaTime)
    {
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

    bool EditorLayer::OnKeyDownEvent(const CC_KeyDownEvent& event)
    {
        if(event.GetKeyCode() == CC_KEYCODE_F1)
        {
            s_ShowTimeStatsOverlay = !s_ShowTimeStatsOverlay;
        }

        return false;
    }

    void EditorLayer::OnImGuiRender()
    {
        EditorWindowBegin();
        
        DrawEditorWindow();

        EditorWindowEnd();
    }
    
    void EditorLayer::EditorWindowBegin()
    {
        static bool pOpen = true;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;
    
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace", &pOpen, window_flags);
        ImGui::PopStyleVar(3);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        ImGuiStyle& style = ImGui::GetStyle();
        const float minWindowSizeX = style.WindowMinSize.x;
        style.WindowMinSize.x = 300.f;
        
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
        
        style.WindowMinSize.x = minWindowSizeX;        
    }
    
    void EditorLayer::DrawEditorWindow()
    {
        DrawMenuBar();
        DrawSceneWindow();

        DrawHierarchyWindow(s_ShowHierarchy);
        DrawInspectorWindow(s_ShowInspector);
    }

    void EditorLayer::EditorWindowEnd()
    {
        ImGui::End();
    }

    void EditorLayer::DrawMenuBar()
    {
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Exit", NULL, false))
                {
                    Engine::Get().Close();
                }
                ImGui::EndMenu();
            }

            if(ImGui::BeginMenu("Windows"))
            {
                ImGui::MenuItem("Hierarchy##00", NULL, &s_ShowHierarchy);
                ImGui::MenuItem("Inspector##00", NULL, &s_ShowInspector);

                ImGui::EndMenu();
            }

            if(ImGui::BeginMenu("World"))
            {
                if(ImGui::MenuItem("Create Actor##00", NULL))
                    m_EditorWorld->CreateActor("Actor", glm::vec3(0));
                
                ImGui::EndMenu();
            }
            
            ImGui::EndMenuBar();
        }
    }
    
    void EditorLayer::DrawSceneWindow()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Scene");
        ImGui::PopStyleVar();

        m_IsViewportFocused = ImGui::IsWindowFocused();
        m_IsViewportHovered = ImGui::IsWindowHovered();
        Engine::Get().GetImGuiLayer()->SetBlockEvents(!m_IsViewportFocused || !m_IsViewportHovered);
        
        ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        m_ViewportSize = {viewportSize.x , viewportSize.y};
        
        uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
        ImGui::Image(textureID, ImVec2{m_ViewportSize.x, m_ViewportSize.y}, ImVec2{0,1}, ImVec2{1,0});

        ImGui::End();
    }

    void EditorLayer::DrawHierarchyWindow(bool& show)
    {
        if(!show)
            return;
        
        ImGui::Begin("Hierarchy##01", &show);
        
        Editor::ShowAllActors(m_EditorWorld.get());

        if(ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
            Editor::s_SelectedActor = nullptr;
        
        ImGui::End();
    }

    void EditorLayer::DrawInspectorWindow(bool& show)
    {
        if(!show)
            return;

        ImGui::Begin("Inspector##01", &show);

        if(Editor::s_SelectedActor)
            Editor::ShowActor(Editor::s_SelectedActor);

        ImGui::End();
    }
}
