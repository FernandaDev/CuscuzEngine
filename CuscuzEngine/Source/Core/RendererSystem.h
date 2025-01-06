#pragma once

#include <vector>

#include "vec4.hpp"
#include "OrthoCameraController.h"

class IRender;

class RendererSystem
{
	std::unique_ptr<OrthoCameraController> m_Camera;
	
	std::vector<std::weak_ptr<IRender>> m_RenderComponents;
	glm::vec4 m_ClearColor = {0.6f, 0.6f, 0.6f, 1.0f};
	
public:
	RendererSystem();
	~RendererSystem();

	void OnUpdate(float deltaTime);
	void OnEvent(CC_Event& event);
	
	void AddRenderComponent(const std::shared_ptr<IRender>& renderComponent);
	void RemoveRenderComponent(const std::shared_ptr<IRender>& renderComponent);
	void DrawObjects();

	const OrthographicCamera& GetCamera() const { return m_Camera->GetCamera(); }
};

