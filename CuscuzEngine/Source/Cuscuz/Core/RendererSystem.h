#pragma once

#include <vector>
#include "vec4.hpp"
#include "OrthoCameraController.h"

namespace Cuscuz
{
    class IDrawable;

    class RendererSystem
    {
        std::unique_ptr<OrthoCameraController> m_Camera;

        std::vector<std::weak_ptr<IDrawable>> m_RenderComponents;
        glm::vec4 m_ClearColor = {0.6f, 0.6f, 0.6f, 1.0f};

    public:
        RendererSystem();
        ~RendererSystem();

        void OnUpdate(float deltaTime);
        void OnEvent(CuscuzEvent& event);

        void AddRenderComponent(const std::shared_ptr<IDrawable>& renderComponent);
        void RemoveRenderComponent(const std::shared_ptr<IDrawable>& renderComponent);
        void DrawObjects();

        OrthoCameraController& GetCameraController() const { return *m_Camera; }
    };
}
