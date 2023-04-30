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
	return IsOpen() && ImGui::BeginMainMenuBar();
}

void WMainImGui::End()
{
	HandleKeyboardInputs();
	ImGui::EndMainMenuBar();

	if (!IsOpen())
	{
		glfwSetWindowShouldClose(m_window, 1);
	}
}

void WMainImGui::RenderContent()
{
	if (ImGui::BeginMenu("File"))
	{
		// clang-format off
		if (ImGui::MenuItem("New")) { }
		if (ImGui::MenuItem("Open")) { }
		if (ImGui::MenuItem("Save")) { }
		// clang-format on
		if (ImGui::MenuItem("Close", "Esc"))
		{
			Close();
		}

		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Edit"))
	{
		ImGui::SeparatorText("Add shapes");

		if (ImGui::MenuItem("Add rectangle", "Ctrl+N+R"))
		{
			m_addShapeEventSignal(ShapeType::Rectangle);
		}
		if (ImGui::MenuItem("Add triangle", "Ctrl+N+T"))
		{
			m_addShapeEventSignal(ShapeType::Triangle);
		}
		if (ImGui::MenuItem("Add ellipse", "Ctrl+N+E"))
		{
			m_addShapeEventSignal(ShapeType::Ellipse);
		}

		ImGui::SeparatorText("History");

		// clang-format off
		if (ImGui::MenuItem("Undo", "Ctrl+Z", false, false)) { }
		if (ImGui::MenuItem("Redo", "Ctrl+Y", false, false)) { }
		// clang-format on

		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Options"))
	{
		if (ImGui::MenuItem("Toggle grid"))
		{
			m_gridToggleSignal();
		}

		ImGui::Separator();

		if (ImGui::MenuItem("Switch theme"))
		{
			m_isLightTheme
				? ImGui::StyleColorsDark()
				: ImGui::StyleColorsLight();
			m_isLightTheme = !m_isLightTheme;
		}

		ImGui::EndMenu();
	}
}

WMainImGui::Connection WMainImGui::OnGridToggle(const OnGridToggleCallback& handler)
{
	return m_gridToggleSignal.connect(handler);
}

WMainImGui::Connection WMainImGui::OnAddShape(const OnAddShapeCallback& handler)
{
	return m_addShapeEventSignal.connect(handler);
}

void WMainImGui::EmmitAddShape(ShapeType type)
{
}

void WMainImGui::HandleKeyboardInputs()
{
	if (ImGui::IsKeyPressed(ImGuiKey_Escape))
	{
		Close();
	}

	if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl) && ImGui::IsKeyDown(ImGuiKey_N))
	{
		if (ImGui::IsKeyPressed(ImGuiKey_E))
		{
			m_addShapeEventSignal(ShapeType::Ellipse);
		}
		if (ImGui::IsKeyPressed(ImGuiKey_R))
		{
			m_addShapeEventSignal(ShapeType::Rectangle);
		}
		if (ImGui::IsKeyPressed(ImGuiKey_T))
		{
			m_addShapeEventSignal(ShapeType::Triangle);
		}
	}
}

} // namespace app::window
