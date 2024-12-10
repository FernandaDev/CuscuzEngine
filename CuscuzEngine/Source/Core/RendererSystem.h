#pragma once

#include <vector>

#include "vec4.hpp"

class IRender;

class RendererSystem
{
	std::vector<std::weak_ptr<IRender>> m_RenderComponents;
	glm::vec4 m_ClearColor = {0.6f, 0.6f, 0.6f, 1.0f};
	
public:
	RendererSystem() = default;
	~RendererSystem();

	void AddRenderComponent(const std::shared_ptr<IRender>& renderComponent);
	void RemoveRenderComponent(const std::shared_ptr<IRender>& renderComponent);
	void DrawObjects();

	void Update();

	// static void BeginScene();
	// static void EndScene();
	//
	// static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
	//
	// static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
};

