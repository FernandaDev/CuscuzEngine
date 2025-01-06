#pragma once
#include "Camera.h"
#include "Core/CC_Core.h"

class Texture2D;

class Renderer2D
{
public:
    static void Init();
    static void Shutdown();
    
    static void BeginScene(const OrthographicCamera& camera);
    static void EndScene();
    
    static void DrawQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color);
    static void DrawQuad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& color);
    static void DrawQuad(const glm::mat4& worldTransform, const glm::vec4& color, const CC_AssetRef<Texture2D>& texture = nullptr);
};
