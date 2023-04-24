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
	auto windowsCopy = m_windows;
	for (auto& window : windowsCopy)
	{
		window->Update();
	}
}

void WindowManagerImGui::Render()
{
}

void WindowManagerImGui::AddWindow(Window&& window)
{
	m_windows.push_back(std::move(window));
}

} // namespace app::window
