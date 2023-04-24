#pragma once

#include "../../imgui/WindowImGui.h"

#include <GLFW/glfw3.h>

namespace app::window
{

class WMainImGui : public WindowImGui
{
public:
	using MyBase = WindowImGui;

	explicit WMainImGui(GLFWwindow* window);

private:
	// <<abstract>> BaseWindow
	bool Begin() override;
	void End() override;
	// >>>>>>>>>>>>>>>>>>>>>>

	// <<abstract>> WindowImGui
	void RenderContent() final;
	// >>>>>>>>>>>>>>>>>>>>>>>>

	void HandleKeyboardInputs();

	GLFWwindow* m_window;

	bool m_isLightTheme = true;
	bool m_shouldCloseApp = false;
};

} // namespace app::window
