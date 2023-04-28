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

	using CanvasSharedPtr = illusio::canvas::ICanvasSharedPtr;
	CanvasSharedPtr GetCanvas();

	bool IsGridEnabled() noexcept;

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

	using CanvasRenderingBoundInfo = std::tuple<ImVec2, ImVec2, ImVec2>; // pointLeftTop, pointRightBottom, size
	CanvasRenderingBoundInfo GetCanvasRendernBoundInfo() const;

	//ImVec2 m_boundingsSize = ImVec2(5, 10);

	bool m_isGridEnabled = true;
	float m_gridStep = 64.0f;
	ImU32 m_gridColor = IM_COL32(200, 200, 200, 40);
	ImU32 m_backgroundColor = IM_COL32(100, 100, 100, 255);

	ImVec2 m_scrolling = ImVec2(0, 0);

	CanvasSharedPtr m_canvas;

	using DraftDocument = presenter::IDocumentPtr;
	DraftDocument m_draftPresenter;
};

} // namespace app::window
