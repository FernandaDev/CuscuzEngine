#pragma once

#include <vector>

class IRender;

class RendererSystem
{
	std::vector<std::weak_ptr<IRender>> m_RenderComponents;
	
public:
	RendererSystem() = default;
	~RendererSystem();

	void Init() const;

	void AddRenderComponent(const std::shared_ptr<IRender>& renderComponent);
	void RemoveRenderComponent(const std::shared_ptr<IRender>& renderComponent);

	void Update();
	void Render() const;
	
private:
	void Clear() const;
};

