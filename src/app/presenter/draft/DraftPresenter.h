#pragma once

#include <illusio/common/signals/signal.hpp>
#include <illusio/domain/object/positionable/group/IPositionableGroup.h>

#include <app/model/draft/AppModelPositionablesDraft_fwd.h>
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

	FrameOpt GetSelectionFrame() const override;
	// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	Connection DoOnModelChange(const OnModelChangeCallback& callback);

private:
	void ClearSelection();

	using WindowEvent = window::event::WindowEvent;
	using WindowEventType = window::event::WindowEventType;
	void OnViewLeftMouseDown(const WindowEvent& evt);

	using AppModelPositionablesDraft = app::model::AppModelPositionablesDraftSharedPtr;
	AppModelPositionablesDraft m_positionablesDraft;
	void OnModelChange(ConstPositionables positionables, ConstPositionable changed);

	using ConstPositionableSignal = illusio::common::signal<void(ConstPositionables, ConstPositionable)>;
	ConstPositionableSignal m_positionablesChangeSignal;

	using SelectionGroup = illusio::domain::IPositionableGroupSharedPtr;
	SelectionGroup m_selectionGroup;

	View m_view;
};

} // namespace app::presenter
