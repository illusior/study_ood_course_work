#pragma once

#include <tuple>

#include <illusio/canvas/ICanvas.h>
#include <illusio/domain/object/positionable/shape/ShapeTypes.h>

#include "../../imgui/WindowImGui.h"

#include "app/presenter/IDocument.h"

namespace app::window
{

class WDraftEditorImGui final : public WindowImGui
{
public:
	using MyBase = WindowImGui;

	explicit WDraftEditorImGui();

	void ToggleGrid() noexcept;
	using ShapeType = illusio::domain::shape::ShapeType;
	void AddShape(ShapeType type);
	void ChangeInsertShapeType(ShapeType type);

	using CanvasSharedPtr = illusio::canvas::ICanvasSharedPtr;
	CanvasSharedPtr GetCanvas();

	bool IsGridEnabled() noexcept;

	using OnScrollingCallback = std::function<void(const ImVec2&)>;
	using Connection = illusio::common::connection;
	Connection OnScrollingChange(const OnScrollingCallback& handler);

private:
	// <<abstract>> BaseWindow
	bool Begin() override;
	void End() override;
	// >>>>>>>>>>>>>>>>>>>>>>

	// <<abstract>> WindowImGui
	void RenderContent() override;
	// >>>>>>>>>>>>>>>>>>>>>

	void AddDraftGridToCanvas();
	void ResetCanvas();
	void HandleInput();

	bool m_isGridEnabled = true;
	float m_gridStep = 64.0f;
	ImU32 m_gridColor = IM_COL32(200, 200, 200, 40);
	ImU32 m_backgroundColor = IM_COL32(100, 100, 100, 255);

	ImVec2 m_scrolling = ImVec2(0, 0);
	using ScrollingChangeSignal = illusio::common::signal<void(const ImVec2&)>;
	ScrollingChangeSignal m_scrollingChangeSignal;

	CanvasSharedPtr m_canvas;

	using DraftDocument = presenter::IDocumentPtr;
	DraftDocument m_draftPresenter;
};

} // namespace app::window
