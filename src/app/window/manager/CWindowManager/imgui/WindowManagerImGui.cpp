#include "pch.h"

#include "WindowManagerImGui.h"

#include "app/window/CWindow/imgui/backends/ImGuiBackends.h"

namespace app::window
{

WindowManagerImGui::WindowManagerImGui()
{
}

WindowManagerImGui::~WindowManagerImGui()
{
}

void WindowManagerImGui::Update()
{
	//auto windowsCopy = m_windows;
	for (auto& window : m_windows)
	{
		window->Update();
	}
}

void WindowManagerImGui::Render()
{
}

void WindowManagerImGui::AddWindow(Window&& window)
{
	auto alreadyHasThatWindow = (std::find(m_windows.begin(), m_windows.end(), window) != m_windows.end());
	if (alreadyHasThatWindow)
	{
		return;
	}

	m_windows.push_back(std::move(window));
}

} // namespace app::window
