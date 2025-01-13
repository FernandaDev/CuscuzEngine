#pragma once
#include "Camera.h"
#include "Core/CC_Core.h"

class Texture2D;
class TransformComponent;

class Renderer2D
{
public:
    static void Init();
    static void Shutdown();
    
    static void BeginScene(const OrthographicCamera& camera);
    static void EndScene();
    static void Flush();
    
    static void DrawQuad(const TransformComponent& transform, const glm::vec4& color);
    static void DrawQuad(const TransformComponent& transform, const glm::vec4& color,
        const CC_AssetRef<Texture2D>& texture, const glm::vec2& tilingOffset = glm::vec2(1.0f));
};
