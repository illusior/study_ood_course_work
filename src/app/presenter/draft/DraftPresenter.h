#pragma once

#include <illusio/domain/object/positionable/group/IPositionableGroup.h>
#include <illusio/domain/common/frame/CFrame/FrameD.h>

#include <app/window/CWindow/draft_editor/imgui/WDraftEditorImGui.h>

#include "../IPositionablesDraftPresenter.h"

namespace app::presenter
{

class DraftPresenter final : public IPositionablesDraftPresenter
{
public:
	using View = window::WDraftEditorImGui*;
	explicit DraftPresenter(View windowDraft);

	// <<interface>> IPositionablesDraftPresenter
	void AddShape(ShapeType shapeType, const Point& startPoint, const Size& size) override;
	void RemovePositionablesSelection() override;

	bool IsPointHoversPositionable(const Point& p) const noexcept override;
	// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	Connection DoOnModelChange(const OnModelChangeCallback& callback) override;

	Connection DoOnSelectionFrameChange(const OnSelectionFrameChangeCallback& handler) override;

private:
	using WindowEvent = window::event::WindowEvent;
	using WindowEventType = window::event::WindowEventType;
	using WindowDraftEditorEvent = window::event::WindowDraftEditorEvent;
	void OnViewLeftMouseDown(const WindowEvent& evt);
	void OnViewLeftMouseUp(const WindowEvent& evt);
	void OnViewKeyboardDown(const WindowEvent& evt);
	void OnViewDraggingPositionable(const WindowEvent& evt);
	void OnViewDraggingReszieInfoUpdate(bool isViewResizingItem, bool isViewDraggingItem);
	void OnViewResizeSelection(const WindowDraftEditorEvent& evt);

	using AppModelPositionablesDraft = illusio::domain::IPositionableGroupSharedPtr;
	AppModelPositionablesDraft m_positionablesDraft;
	void OnModelChange(const DomainPositionableModelEvent& evt);

	void ClearSelection();
	void RemovePositionablesSelectionFromModel();
	void MoveSelectionToRenderTop();
	void SetDraggingInfo(const WindowEvent& evt);

	void EmitSelectionFrameChangeSignal();

	using ConstPositionableSignal = illusio::common::signal<void(const DomainPositionableModelEvent&)>;
	ConstPositionableSignal m_positionablesChangeSignal;

	using SelectionGroup = illusio::domain::IPositionableGroupSharedPtr;
	SelectionGroup m_selectionGroup;

	using SelectionFrameChangeSignal = illusio::common::signal<void(const FrameOpt&)>;
	SelectionFrameChangeSignal m_frameChangedSignal;

	View m_view;

	bool m_draggingItemAtView = false;
	bool m_resizingItemAtView = false;
	bool m_dragResizeInfoMustBeUpdated = true;
	Point m_dragStartAtPoint = Point{ 0.0, 0.0 };
	Point m_dragStartAtPoint_leftTopSelection_delta = Point{ 0.0, 0.0 };
	Point m_selectionStartLeftTop = Point{ 0.0, 0.0 };
	Size m_selectionStartSize;
};

} // namespace app::presenter
