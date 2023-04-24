#include "pch.h"

#include "Application.h"

#include "window/Layout.h"

#include "window/CWindow/imgui/backends/ImGuiBackends.h"
#include "window/manager/CWindowManager/imgui/WindowManagerImGui.h"

#include "window/Layout.h"

namespace app
{

GLFWwindow* applicationWindow = nullptr;

Application& Application::GetInstance()
{
	static auto app = Application{};

	return app;
}

using namespace window;

Application::Application()
	: m_windowManager(
		std::make_unique<WindowManagerImGui>())
{
	ImGuiBackends::Init(applicationWindow);
}

Application::~Application()
{
	ImGuiBackends::DeInit(applicationWindow);
}

void Application::Start()
{
	DefaultLayout(*m_windowManager, applicationWindow);

	while (!glfwWindowShouldClose(applicationWindow))
	{
		ImGuiBackends::DrawBegin(ImGuiBackends::using_glfw_opengl3{});

		m_windowManager->Update();
		// ImGui::ShowDemoWindow();

		ImGuiBackends::DrawEnd(applicationWindow);
	}
}

} // namespace app
