#pragma once

#include <SDL_render.h>
#include "glm.hpp"
#include "SpriteRenderer.h"

class Animation2DComponent : public SpriteRenderer
{
    int m_FrameCount;
    float m_AnimFPS;
    float m_CurrentFrame;

    SDL_Rect m_Source{};
    SDL_Rect m_Destination{};

    glm::i32vec2 m_SingleSpriteSize = { 80, 110 }; 
    
public:
    Animation2DComponent() = default;
    Animation2DComponent(int frameCount, int drawOrder = 0);
    ~Animation2DComponent() override = default;
    
    void Update(float deltaTime) override;
    void Draw() override;

    float GetAnimFPS() const { return m_AnimFPS; }
    void SetAnimFPS(float fps) { m_AnimFPS = fps; }

    REGISTER_COMPONENT(Animation2DComponent);

private:
    void PlayFrame(int x, int y);
};
