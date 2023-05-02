#pragma once

#include <tuple>

#include <illusio/canvas/ICanvas.h>
#include <illusio/domain/object/positionable/shape/ShapeTypes.h>

#include "../../imgui/WindowImGui.h"

#include "app/presenter/IPositionablesDraftPresenter.h"

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
	void RemovePositionablesSelectionFromDraft();

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
	void AddDraftContentToCanvas();
	void AddSelectionFrameToCanvas();
	void AddOverlay();
	void ResetCanvas();

	void HandleInput();

	void HandleMouseInput();
	void HandleMouseLeftButton();
	void HandleMouseRightButton();
	void HandleMouseCursorStyle();

	using DomainPositionableModelEvent = presenter::IPositionablesDraftPresenter::DomainPositionableModelEvent;
	void OnPresenterModelChange(const DomainPositionableModelEvent& evt);

	using CanvasRenderingBoundInfo = std::tuple<ImVec2, ImVec2, ImVec2>; // pointLeftTop, pointRightBottom, size
	CanvasRenderingBoundInfo GetCanvasRendernBoundInfo() const;

	bool m_isGridEnabled = true;
	float m_gridStep = 64.0f;
	ImU32 m_gridColor = IM_COL32(200, 200, 200, 40);
	ImU32 m_backgroundColor = IM_COL32(100, 100, 100, 255);

	ImU32 m_selectionFrameColor = IM_COL32(0, 255, 0, 255);
	float m_selectionFrameThikness = 1.0f;

	ImVec2 m_scrolling = ImVec2(0, 0);

	CanvasSharedPtr m_canvas;

	using DraftDocument = presenter::IPositionablesDraftPresenterPtr;
	DraftDocument m_draftPresenter;

	decltype(DomainPositionableModelEvent::PositionablesGroup) m_modelSnapshot;
};

} // namespace app::window
