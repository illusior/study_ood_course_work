#pragma once

#include <functional>
#include <optional>
#include <tuple>
#include <vector>

#include <illusio/canvas/ICanvas.h>
#include <illusio/common/signals/signal.hpp>
#include <illusio/domain/object/positionable/shape/ShapeTypes.h>

#include "../../imgui/WindowImGui.h"

#include "app/presenter/IPositionablesDraftPresenter.h"
#include "app/window/CWindow/draft_editor/event/WindowDraftEditorEvent.h"

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

	bool IsGridEnabled() const noexcept;

	using OnPositionableResizeCallback = std::function<void(const window::event::WindowDraftEditorEvent&)>;
	Connection DoOnPositionableResize(const OnPositionableResizeCallback& handler);

	using OnDraggingResizingCallback = std::function<void(bool, bool)>;
	Connection DoOnDraggingResizing(const OnDraggingResizingCallback& handler);

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
	void AddSelectionFrameResizerMarks();
	void AddOverlay();
	void ResetCanvas();

	void HandleInput();

	void HandleMouseInput();
	void HandleMouseLeftButtonClicked();
	void HandleMouseLeftButtonDraggingOverWorkArea();
	void HandleMouseLeftButtonDraggingOverResizers();
	void HandleMouseRightButton();
	void HandleMouseUp();

	void HandleMouseCursorStyle();
	void HandleMouseCursorStyleOverResizers();

	using CanvasRenderingBoundInfo = std::tuple<ImVec2, ImVec2, ImVec2>; // pointLeftTop, pointRightBottom, size
	CanvasRenderingBoundInfo GetCanvasRendernBoundInfo() const;

	using FrameOpt = presenter::IPositionablesDraftPresenter::FrameOpt;
	void OnPresenterSelectionFrameChange(const FrameOpt& frame);
	void CalculateResizersCornerPoints();
	using ResizeDirection = window::event::ResizeDirection;
	using ResizeDirectionOpt = std::optional<ResizeDirection>;
	ResizeDirectionOpt GetResizeDirection() const noexcept;

	using DomainPositionableModelEvent = presenter::IPositionablesDraftPresenter::DomainPositionableModelEvent;
	void OnPresenterModelChange(const DomainPositionableModelEvent& evt);

	bool m_isGridEnabled = true;
	float m_gridStep = 64.0f;
	ImU32 m_gridColor = IM_COL32(200, 200, 200, 40);
	ImU32 m_backgroundColor = IM_COL32(100, 100, 100, 255);

	ImU32 m_selectionFrameColor = IM_COL32(0, 255, 0, 255);
	float m_selectionFrameThikness = 1.0f;
	size_t m_selectionFrameMarkersCount = 8;
	float m_selectionFrameMarkersSize = 10.0f;
	float m_selectionFrameMarkersPadding = 2.0f;
	ImU32 m_selectionFrameMarekrsFillColor = IM_COL32(123, 213, 255, 255);

	ImVec2 m_scrolling = ImVec2(0, 0);

	using CanvasSharedPtr = illusio::canvas::ICanvasSharedPtr;
	CanvasSharedPtr m_canvas;

	using ResizePositionableSignal = illusio::common::signal<void(const window::event::WindowDraftEditorEvent&)>;
	ResizePositionableSignal m_resizePositionableSignal;

	using ResizingDraggingSignal = illusio::common::signal<void(bool, bool)>;
	ResizingDraggingSignal m_resizingDraggingInfoSignal;

	using DraftDocument = presenter::IPositionablesDraftPresenterPtr;
	DraftDocument m_draftPresenter;

	decltype(DomainPositionableModelEvent::PositionablesGroup) m_modelSnapshot;

	FrameOpt m_selectionFrame{};

	using Points = std::vector<illusio::domain::common::axes::PointD>;
	Points m_resizersOppositeCorners{};
};

} // namespace app::window
