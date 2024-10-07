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
    Animation2DComponent(int frameCount, int drawOrder = 0, SDL_BlendMode blendMode = SDL_BLENDMODE_NONE);
    ~Animation2DComponent() override = default;
    
    void Update(float deltaTime) override;
    void Draw(SDL_Renderer* renderer) override;

    float GetAnimFPS() const { return m_AnimFPS; }
    void SetAnimFPS(float fps) { m_AnimFPS = fps; }

    REGISTER_COMPONENT(Animation2DComponent);

private:
    void PlayFrame(int x, int y);
};
