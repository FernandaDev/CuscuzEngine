#include "pch.h"
#include "ImGuiLayer.h"

#include "EventSystem.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"
#include "Events/EventHandler.h"
#include "Utils/Log.h"

ImGuiLayer::ImGuiLayer(const Window& Window, SDL_Renderer* Renderer):
m_Renderer(*Renderer)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForSDLRenderer(Window.GetWindow(), Renderer);
	ImGui_ImplSDLRenderer_Init(Renderer);

	m_ShowDemoWindow = true;
	m_ShowAnotherWindow = false;
	m_ClearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	SUBSCRIBE_SDL_EVENT(this, ImGuiLayer::OnSDLEvent);
}

ImGuiLayer::~ImGuiLayer()
{
	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiLayer::Update()
{
	ImGui_ImplSDLRenderer_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	if(m_ShowDemoWindow)
		ImGui::ShowDemoWindow(&m_ShowDemoWindow);

	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &m_ShowDemoWindow);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &m_ShowAnotherWindow);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&m_ClearColor); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (m_ShowAnotherWindow)
	{
		ImGui::Begin("Another Window", &m_ShowAnotherWindow);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			m_ShowAnotherWindow = false;
		ImGui::End();
	}
}

void ImGuiLayer::Render()
{
	const ImGuiIO io = ImGui::GetIO();

	ImGui::Render();
	SDL_RenderSetScale(&m_Renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
	ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::OnSDLEvent(const SDL_Event& Event)
{
	ImGui_ImplSDL2_ProcessEvent(&Event);
}



