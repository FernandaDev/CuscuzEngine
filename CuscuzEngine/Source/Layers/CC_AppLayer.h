#pragma once

#include "Layer.h"

class CC_Game;

class CC_AppLayer : public Layer
{
    std::shared_ptr<CC_Game> m_Game;
    bool m_ShowPlayWindow;
    
public:
    CC_AppLayer(const std::shared_ptr<CC_Game>& game);

    void OnUpdate() override;
    void OnImGuiRender() override;
    void OnEvent(CC_Event& event) override;

private:
    bool ToggleMainWindow(const class CC_KeyDownEvent& event);
    void ShowPlayWindow();
};
