#pragma once

#include "Cuscuz/Layers/Layer.h"

class CC_KeyDownEvent;
class World;

class EditorLayer : public Cuscuz::Layer
{
    bool m_ShowWorldWindow;
    bool m_ShowTimeStatsOverlay;
    World* m_World;

public:
    EditorLayer();
    ~EditorLayer() override = default;

    void OnAttach() override
    {
    }

    //void OnUpdate(float deltaTime) override;
    void OnImGuiRender() override;
    void OnEvent(Cuscuz::CuscuzEvent& event) override;

private:
    bool ToggleWindow(const CC_KeyDownEvent& event);
    void ShowWorldWindow();
};
