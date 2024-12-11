#pragma once

#include "Layers/Layer.h"

class CC_KeyDownEvent;
class World;

class EditorLayer : public Layer
{
    bool m_ShowWorldWindow;
    World* m_World;
    
public:
    EditorLayer();
    ~EditorLayer() override = default;

    void OnAttach() override {}
    //void OnUpdate(float deltaTime) override;
    void OnImGuiRender() override;
    void OnEvent(CC_Event& event) override;

private:
    bool ToggleWindow(const CC_KeyDownEvent& event);
    void ShowWorldWindow();
};
