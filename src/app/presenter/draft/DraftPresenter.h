#pragma once

#include <illusio/common/signals/signal.hpp>
#include <illusio/domain/object/positionable/group/IPositionableGroup.h>

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

	FrameOpt GetSelectionFrame() const override;
	// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	Connection DoOnModelChange(const OnModelChangeCallback& callback);

private:
	using WindowEvent = window::event::WindowEvent;
	using WindowEventType = window::event::WindowEventType;
	void OnViewLeftMouseDown(const WindowEvent& evt);
	void OnViewKeyboardDown(const WindowEvent& evt);
	void OnViewLeftMouseDragging(const WindowEvent& evt);

	using AppModelPositionablesDraft = illusio::domain::IPositionableGroupSharedPtr;
	AppModelPositionablesDraft m_positionablesDraft;
	void OnModelChange(const DomainPositionableModelEvent& evt);

	void ClearSelection();
	void RemovePositionablesSelectionFromModel();
	void MoveSelectionToTop();

	using ConstPositionableSignal = illusio::common::signal<void(const DomainPositionableModelEvent&)>;
	ConstPositionableSignal m_positionablesChangeSignal;

	using SelectionGroup = illusio::domain::IPositionableGroupSharedPtr;
	SelectionGroup m_selectionGroup;

	View m_view;

	bool m_dragging = false;
	Point m_dragStartAtPoint = Point{ 0.0, 0.0 };
	Point m_dragStartAtPoint_leftTopSelection_delta = Point{ 0.0, 0.0 };
};

} // namespace app::presenter
