﻿#pragma once

#include "Camera.h"
#include <Cuscuz/Core/Core.h>

namespace Cuscuz
{
    class SubTexture2D;
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
    
        static void DrawQuad(const glm::mat4& worldTransform, const glm::vec4& color);
        static void DrawQuad(const glm::mat4& worldTransform, const glm::vec4& color,
            const CC_AssetRef<Texture2D>& texture, const glm::vec2& tilingOffset = glm::vec2(1.0f));
        static void DrawQuad(const glm::mat4& worldTransform, const glm::vec4& color,
            const CC_AssetRef<SubTexture2D>& subTexture, const glm::vec2& tilingOffset = glm::vec2(1.0f));

        struct Statistics
        {
            uint32_t DrawCalls = 0;
            uint32_t QuadCount = 0;

            uint32_t GetTotalVertexCount() const { return QuadCount * 4; }
            uint32_t GetTotalIndexCount() const { return QuadCount * 6; }
        };

        static void ResetStats();
        static Statistics GetStats();

    private:
        static void NextBatch();
        static void StartBatch();
    };
}