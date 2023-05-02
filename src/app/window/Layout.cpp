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

	mainWindow->DoOnGridToggle([draft = draftEditorWindow.get()]() noexcept {
		draft->ToggleGrid();
	});
	using ShapeType = illusio::domain::shape::ShapeType;
	mainWindow->DoOnAddShape([draft = draftEditorWindow.get()](ShapeType type) noexcept {
		draft->AddShape(type);
	});
	mainWindow->DoOnRemoveShapeSelection([draft = draftEditorWindow.get()]() {
		draft->RemovePositionablesSelectionFromDraft();
	});

	windowManager.AddWindow(std::move(mainWindow));
	windowManager.AddWindow(std::move(draftEditorWindow));
}

} // namespace app::window
