#include "pch.h"

#include "WMainImGui.h"

namespace app::window
{

constexpr auto TITLE = "Main Menu Bar";

WMainImGui::WMainImGui(GLFWwindow* window)
	: MyBase(TITLE)
	, m_window(window)
{
	if (m_window == nullptr)
	{
		throw std::runtime_error(std::string("Failed to init ") + TITLE);
	}
}

bool WMainImGui::Begin()
{
	HandleKeyboardInputs();

	return IsOpen();
}

void WMainImGui::End()
{
	if (m_shouldCloseApp)
	{
		glfwSetWindowShouldClose(m_window, 1);
	}
}

void WMainImGui::RenderContent()
{
	// clang-format off
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New")) { }
			if (ImGui::MenuItem("Open")) { }
			if (ImGui::MenuItem("Save")) { }
			if (ImGui::MenuItem("Close", "Esc"))
			{
				m_shouldCloseApp = true;
			}

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "Ctrl+Z", false, false)) { }
			if (ImGui::MenuItem("Redo", "Ctrl+Y", false, false)) { }
			ImGui::Separator();


			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Options"))
		{
			if (ImGui::MenuItem("Switch theme"))
			{
				m_isLightTheme
					? ImGui::StyleColorsDark()
					: ImGui::StyleColorsLight();
				m_isLightTheme = !m_isLightTheme;
			}

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	} // clang-format on
}

void WMainImGui::HandleKeyboardInputs()
{
	if (ImGui::IsKeyPressed(ImGuiKey_Escape))
	{
		m_shouldCloseApp = true;
	}
}

} // namespace app::window
