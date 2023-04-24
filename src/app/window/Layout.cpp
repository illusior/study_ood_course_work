#include "pch.h"

#include "Layout.h"

#include "CWindow/main/imgui/WMainImGui.h"
#include "CWindow/draft_editor/imgui/WDraftEditorImGui.h"

namespace app::window
{

void DefaultLayout(IWindowManager& windowManager, GLFWwindow* window)
{
	windowManager.AddWindow(std::make_shared<window::WMainImGui>(window));
	windowManager.AddWindow(std::make_shared<window::WDraftEditorImGui>());
}

} // namespace app::window
