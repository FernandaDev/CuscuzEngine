#pragma once

#include "Cuscuz/Events/CuscuzEvent.h"
#include "Cuscuz/Events/KeyEvents.h"
#include "Cuscuz/Layers/Layer.h"

namespace Cuscuz
{
    class Actor;
    class Window;
    class CC_Game;

    class ImGuiLayer : public Layer
    {
        bool m_ShowDemoWindow;
        bool m_BlockEvents = true;
    
    public:
        ImGuiLayer(const Window& window);
        ~ImGuiLayer() override;

        void OnAttach() override;
        void OnDetach() override;
        void OnImGuiRender() override;
        void OnEvent(CuscuzEvent& event) override;
        void SetBlockEvents(bool block) { m_BlockEvents = block; } 

        void Begin();
        void End();
    private:
        bool OnSDLEvent(const class CC_SDLEvent& event);
        bool OnKeyDown(const class CC_KeyDownEvent& event);
        bool ToggleMainWindow(const CC_KeyDownEvent& event);
        void ShowMainWindow();
    };
}