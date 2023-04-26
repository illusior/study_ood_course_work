#include "pch.h"

#include <illusio/domain/object/positionable/shape/ShapeTypes.h>

#include "Layout.h"

#include "CWindow/draft_editor/imgui/WDraftEditorImGui.h"
#include "CWindow/main/imgui/WMainImGui.h"

namespace app::window
{

void DefaultLayout(IWindowManager& windowManager, GLFWwindow* window)
{
	auto mainWindow = std::make_unique<window::WMainImGui>(window);
	auto draftEditorWindow = std::make_unique<window::WDraftEditorImGui>();

	mainWindow->OnGridToggle([draft = draftEditorWindow.get()]() noexcept {
		draft->ToggleGrid();
	});
	using ShapeType = illusio::domain::shape::ShapeType;
	mainWindow->OnAddShape([draft = draftEditorWindow.get()](ShapeType type) noexcept {
		draft->AddShape(type);
	});

	windowManager.AddWindow(std::move(mainWindow));
	windowManager.AddWindow(std::move(draftEditorWindow));
}

} // namespace app::window
