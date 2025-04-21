#include "EditorLayer.h"

#include "Cuscuz/core/Input.h"
#include "Cuscuz/GUI/ImGuiLayer.h"
#include "Cuscuz/Utils/FileUtils.h"
#include "Cuscuz/Utils/Instrumentor.h"
#include "Cuscuz/Utils/PlatformUtils.h"
#include "Cuscuz/World/LevelSerializer.h"
#include "ImGui/imgui.h"
#include "Utils/Editor_ActorCreation.h"
#include "Utils/Editor_Settings.h"
#include "Utils/Editor_World.h"

namespace Cuscuz
{
    static bool s_ShowHierarchy = true;
    static bool s_ShowInspector = true;
    static bool s_ShowRendererStats = false;
    static bool s_ShowTimeStatsOverlay = false;

    EditorLayer::EditorLayer() :
    m_CameraController(std::make_unique<OrthoCameraController>(static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT), true)),
    m_EditorWorld(std::make_unique<World>()),
    m_EditorScene(std::make_unique<Scene>())
    {  }
 
    void EditorLayer::OnAttach()
    {
        FramebufferSpecification spec;
        spec.Width =  SCREEN_WIDTH;
        spec.Height = SCREEN_HEIGHT;
        m_Framebuffer = Framebuffer::Create(spec);
    }

    void EditorLayer::OnEvent(CuscuzEvent& event)
    {
        Layer::OnEvent(event);

        m_CameraController->OnEvent(event);
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
            m_CameraController->OnResize(m_ViewportSize.x, m_ViewportSize.y);
            m_EditorScene->OnViewPortResize(static_cast<uint32_t>(m_ViewportSize.x), static_cast<uint32_t>(m_ViewportSize.y));
        }
        
        if(m_IsViewportFocused)
            m_CameraController->OnUpdate(deltaTime);
    
        m_EditorWorld->Update(deltaTime);

        Renderer2D::ResetStats();

        m_Framebuffer->Bind();
    
        RenderCommand::SetClearColor({0.6f, 0.6f, 0.6f, 1.0f});
        RenderCommand::Clear();
    
        //m_EditorScene->OnRender();
        m_EditorScene->OnRender(m_CameraController->GetCamera());

        m_Framebuffer->Unbind();
    }

    bool EditorLayer::OnKeyDownEvent(const CC_KeyDownEvent& event)
    {
        if(event.GetKeyCode() == CC_KEYCODE_F1)
        {
            s_ShowTimeStatsOverlay = !s_ShowTimeStatsOverlay;
            return false;
        }

        const bool shiftPressed = Input::IsKeyPressed(CC_KeyCode::LShift) || Input::IsKeyPressed(CC_KeyCode::RShift);
        const bool controlPressed = Input::IsKeyPressed(CC_KeyCode::LCtrl) || Input::IsKeyPressed(CC_KeyCode::RCtrl);

        switch (event.GetKeyCode())
        {
        case CC_KeyCode::N:
            if(controlPressed)
                NewLevel();

            break;
        case CC_KeyCode::O:
            if(controlPressed)
                OpenLevel();
            
            break;
        case CC_KeyCode::S:
            if(shiftPressed)
                SaveLevel();
            
            break;
        default:
            return false;
        }

        return false;
    }
    
    void EditorLayer::NewLevel()
    {
        CC_AssetRef<Level> newLevel = CreateAssetRef<Level>("Untitled");
        m_EditorWorld->LoadLevel(std::move(newLevel));
        Editor::s_SelectedActor = nullptr;
    }

    void EditorLayer::OpenLevel()
    {
        const std::string filepath = FileDialogs::OpenFile("Level (*.level)\0*.level\0");

        if(!filepath.empty())
        {
            CC_AssetRef<Level> newLevel = CreateAssetRef<Level>(Utils::ExtractNameFromFile(filepath));
            {
                LevelSerializer serializer(newLevel);
                serializer.Deserialize(filepath);
            }
            m_EditorWorld->LoadLevel(std::move(newLevel));
            Editor::s_SelectedActor = nullptr;
        }
    }

    void EditorLayer::SaveLevel()
    {
        const CC_AssetRef<Level> activeLevel = m_EditorWorld->GetActiveLevel();
        const std::string filepath = FileDialogs::SaveFile("Level (*.level)\0*.level\0", "level", activeLevel->GetName().data());

        if(!filepath.empty())
        {
            LevelSerializer serializer(activeLevel);
            serializer.Serialize(filepath);
        }
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
        DrawRendererStatsWindow(s_ShowRendererStats);
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
                if(ImGui::MenuItem("New Level", "Ctrl+N"))
                {
                    NewLevel();
                }
                if(ImGui::MenuItem("Open Level...", "Ctrl+O"))
                {
                    OpenLevel();
                }
                if(ImGui::MenuItem("Save Level As...", "Ctrl+Shift+S"))
                {
                    SaveLevel();
                }
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
                ImGui::MenuItem("RendererStats##00", NULL, &s_ShowRendererStats);

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

    void EditorLayer::DrawRendererStatsWindow(bool& show)
    {
        if(!show)
            return;

        ImGui::Begin("RendererStats##01", &show);

        Editor::ShowRendererStatsWindow();

        ImGui::End();
    }
}
