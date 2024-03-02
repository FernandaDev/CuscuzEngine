#pragma once
#include "SpriteComponent.h"

class Animation2DComponent : public SpriteComponent
{
    int m_FrameCount;
    float m_AnimFPS;
    float m_CurrentFrame;

    SDL_Rect m_Source{};
    SDL_Rect m_Destination{};

    glm::i32vec2 m_SingleSpriteSize = { 80, 110 }; 
    
public:
    Animation2DComponent(int FrameCount, int DrawOrder = 0, SDL_BlendMode BlendMode = SDL_BLENDMODE_NONE);
    ~Animation2DComponent() override = default;
    
    void Update(float DeltaTime) override;
    void Draw(SDL_Renderer* Renderer) override;

    float GetAnimFPS() const { return m_AnimFPS; }
    void SetAnimFPS(float fps) { m_AnimFPS = fps; }

private:
    void PlayFrame(int X, int Y);
};
