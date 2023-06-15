#include "pch.h"

#include <illusio/domain/object/positionable/shape/solid/CShapeSolid/ellipse/CEllipse/Ellipse.h>
#include <illusio/domain/object/positionable/shape/solid/CShapeSolid/rectangle/CRectangle/Rectangle.h>
#include <illusio/domain/object/positionable/shape/solid/CShapeSolid/triangle/CTriangle/Triangle.h>

#include <illusio/domain/common/style/CStyle/Style.h>

#include <illusio/domain/object/positionable/group/CPositionableGroup/PositionableGroup.hpp>

#include "DraftPresenter.h"

namespace app::presenter
{

using IPositionableGroup = illusio::domain::IPositionableGroup;
using PositionableGroup = illusio::domain::PositionableGroup<IPositionableGroup>;

DraftPresenter::DraftPresenter(View windowDraft)
	: m_positionablesDraft(PositionableGroup::Create())
	, m_view(windowDraft)
	, m_selectionGroup(PositionableGroup::Create())
{
	if (m_view == nullptr)
	{
		throw std::logic_error("[app][presenter] DraftPresenter must be initialized with View. Null given");
	}

	m_positionablesDraft->DoOnChange(std::bind(&DraftPresenter::OnModelChange,
		this, std::placeholders::_1));
	m_view->DoOnFiringWindowEvent(std::bind(&DraftPresenter::OnViewDraggingPositionable,
		this, std::placeholders::_1));
	m_view->DoOnDraggingResizing(std::bind(&DraftPresenter::OnViewDraggingReszieInfoUpdate,
		this, std::placeholders::_1, std::placeholders::_2));
	m_view->DoOnFiringWindowEvent(std::bind(&DraftPresenter::OnViewKeyboardDown,
		this, std::placeholders::_1));
	m_view->DoOnFiringWindowEvent(std::bind(&DraftPresenter::OnViewLeftMouseDown,
		this, std::placeholders::_1));
	m_view->DoOnFiringWindowEvent(std::bind(&DraftPresenter::OnViewLeftMouseUp,
		this, std::placeholders::_1));
	m_view->DoOnPositionableResize(std::bind(&DraftPresenter::OnViewResizeSelection,
		this, std::placeholders::_1));
}

constexpr auto DEFAULT_POSITIONABLE_SIZE = 100;

using Draft = illusio::domain::IPositionableGroupRawPtr;
using Point = DraftPresenter::Point;
using ShapeType = DraftPresenter::ShapeType;
using Size = DraftPresenter::Size;

void AddShapeToDraft(Draft draft, ShapeType shapeType, const Point& startPoint, const Size& size)
{
	using Style = illusio::domain::common::Style;

	auto fillStyle = std::make_unique<Style>(IM_COL32(255, 0, 0, 255));
	auto outlineStyle = std::make_unique<Style>(IM_COL32(0, 0, 255, 255));

	illusio::domain::IPositionableSharedPtr positionable = nullptr;

	switch (shapeType)
	{
	case ShapeType::Ellipse: {
		using Ellipse = illusio::domain::shape::solid::Ellipse;

		positionable = std::make_shared<Ellipse>(startPoint,
			size,
			std::move(fillStyle),
			std::move(outlineStyle));

		break;
	}
	case ShapeType::Rectangle: {
		using Rect = illusio::domain::shape::solid::Rectangle;

		positionable = std::make_shared<Rect>(startPoint,
			size,
			std::move(fillStyle),
			std::move(outlineStyle));

		break;
	}
	case ShapeType::Triangle: {
		using Triangle = illusio::domain::shape::solid::Triangle;

		positionable = std::make_shared<Triangle>(startPoint,
			size,
			std::move(fillStyle),
			std::move(outlineStyle));

		break;
	}
	case ShapeType::Unknown:
	default:
		throw std::runtime_error("[app][DraftPresenter] Attempt to insert shape with unknown type");
	}

	draft->InsertPositionable(std::move(positionable));
}

void DraftPresenter::AddShape(ShapeType shapeType, const Point& startPoint, const Size& size)
{
	AddShapeToDraft(m_positionablesDraft.get(), shapeType, startPoint, size);
}

void DraftPresenter::RemovePositionablesSelection()
{
	RemovePositionablesSelectionFromModel();
}

DraftPresenter::Connection DraftPresenter::DoOnModelChange(const OnModelChangeCallback& callback)
{
	return m_positionablesChangeSignal.connect(callback);
}

DraftPresenter::Connection DraftPresenter::DoOnSelectionFrameChange(const OnSelectionFrameChangeCallback& handler)
{
	return m_frameChangedSignal.connect(handler);
}

void DraftPresenter::ClearSelection()
{
	auto posCount = m_selectionGroup->GetPositionablesCount();
	if (posCount == 0)
	{
		return;
	}

	for (; posCount > 0;)
	{
		m_selectionGroup->RemovePositionable(--posCount);
	}
}

void DraftPresenter::RemovePositionablesSelectionFromModel()
{
	const auto posCount = m_selectionGroup->GetPositionablesCount();
	for (size_t i = 0; i < posCount; ++i)
	{
		auto positionable = m_selectionGroup->GetPositionable(i);
		auto positionableIndexAtDraftOpt = m_positionablesDraft->GetPositionableIndex(positionable);
		if (positionableIndexAtDraftOpt.has_value())
		{
			m_positionablesDraft->RemovePositionable(*positionableIndexAtDraftOpt);
		}
	}

	ClearSelection();

	m_frameChangedSignal(m_selectionGroup->GetFrame());
}

void DraftPresenter::MoveSelectionToRenderTop()
{
	const auto posInSelectionCount = m_selectionGroup->GetPositionablesCount();
	const auto posInModelCount = m_positionablesDraft->GetPositionablesCount();
	for (size_t i = 0; i < posInSelectionCount; ++i)
	{
		auto posInSelection = m_selectionGroup->GetPositionable(i);
		auto posWasAtIndex = m_positionablesDraft->GetPositionableIndex(posInSelection);
		m_positionablesDraft->MovePositionableToIndex(*posWasAtIndex, posInModelCount - 1);
	}
}

bool DraftPresenter::IsPointHoversPositionable(const Point& p) const noexcept
{
	return bool(m_positionablesDraft->GetPositionableAtPoint(p));
}

void DraftPresenter::EmitSelectionFrameChangeSignal()
{
	m_frameChangedSignal(m_selectionGroup->GetFrame());
}

void DraftPresenter::SetDraggingInfo(const WindowEvent& evt)
{
	if (!m_dragResizeInfoMustBeUpdated)
	{
		return;
	}

	auto currSelectionFrame = m_selectionGroup->GetFrame();

	m_dragStartAtPoint = Point{
		evt.MouseAt.x,
		evt.MouseAt.y
	};
	m_dragStartAtPoint_leftTopSelection_delta = Point{
		evt.MouseAt.x - currSelectionFrame.pLeftTop.x,
		evt.MouseAt.y - currSelectionFrame.pLeftTop.y
	};

	m_selectionStartLeftTop = currSelectionFrame.pLeftTop;
	m_selectionStartSize = currSelectionFrame.size;

	m_dragResizeInfoMustBeUpdated = false;
}

// ############################################## Handlers ##############################################

void DraftPresenter::OnModelChange(const DomainPositionableModelEvent& evt)
{
	m_positionablesChangeSignal(evt);

	if (evt.EventType != illusio::domain::event::DomainPositionableModelEventTypes::InsertPositionable)
	{
		return;
	}

	ClearSelection();
	if (m_positionablesDraft->GetPositionablesCount() > evt.PositionableChangedAtIndexInGroup)
	{
		auto pos = m_positionablesDraft->GetPositionable(evt.PositionableChangedAtIndexInGroup);
		m_selectionGroup->InsertPositionable(pos);
	}
	EmitSelectionFrameChangeSignal();
}

// ########################################## View event handler ########################################

void DraftPresenter::OnViewKeyboardDown(const WindowEvent& evt)
{
	if (!evt.KeyBoardKeys.contains(window::event::Keyboard::Delete))
	{
		return;
	}

	RemovePositionablesSelectionFromModel();
}

void DraftPresenter::OnViewLeftMouseDown(const WindowEvent& evt)
{
	if (evt.EventType != WindowEventType::MouseDown)
	{
		return;
	}

	auto pos = m_positionablesDraft->GetPositionableAtPoint(evt.MouseAt);
	bool collectingButtonPressed = evt.KeyBoardKeys.contains(window::event::Keyboard::LeftCtrl);
	if (pos == nullptr)
	{ // clicked at empty point (missclicked)
		ClearSelection();
		EmitSelectionFrameChangeSignal();
		return;
	}

	auto posIndexInSelection = m_selectionGroup->GetPositionableIndex(pos);
	auto isPosInSelection = posIndexInSelection.has_value();
	if (collectingButtonPressed && isPosInSelection)
	{
		m_selectionGroup->RemovePositionable(*posIndexInSelection);
		EmitSelectionFrameChangeSignal();
		return;
	}
	if (!collectingButtonPressed && !isPosInSelection)
	{
		ClearSelection();
	}
	if (!isPosInSelection)
	{
		m_selectionGroup->InsertPositionable(pos);
	}

	MoveSelectionToRenderTop();

	EmitSelectionFrameChangeSignal();
}

void DraftPresenter::OnViewLeftMouseUp(const WindowEvent& evt)
{
	if (evt.EventType != window::event::WindowEventType::MouseUp)
	{
		return;
	}

	m_dragResizeInfoMustBeUpdated = true;
}

void DraftPresenter::OnViewDraggingPositionable(const WindowEvent& evt)
{
	if (!m_draggingItemAtView || // clang-format off
		(evt.EventType != window::event::WindowEventType::MouseDrag ||
			m_selectionGroup->GetPositionablesCount() == 0)) // clang-format on
	{
		return;
	}

	SetDraggingInfo(evt);

	auto currSelectionFrame = m_selectionGroup->GetFrame();

	currSelectionFrame.pLeftTop.x = m_dragStartAtPoint.x + evt.DragDelta.x - m_dragStartAtPoint_leftTopSelection_delta.x;
	currSelectionFrame.pLeftTop.y = m_dragStartAtPoint.y + evt.DragDelta.y - m_dragStartAtPoint_leftTopSelection_delta.y;

	m_selectionGroup->SetFrame(currSelectionFrame);

	EmitSelectionFrameChangeSignal();
}

void DraftPresenter::OnViewDraggingReszieInfoUpdate(bool resizing, bool dragging)
{
	m_draggingItemAtView = dragging;
	m_resizingItemAtView = resizing;
}

using ReziseDirection = window::event::ResizeDirection;
static const std::set<ReziseDirection> TopDirection{
	ReziseDirection::N,
	ReziseDirection::NE,
	ReziseDirection::NW
};

static const std::set<ReziseDirection> RightDirection{
	ReziseDirection::NE,
	ReziseDirection::E,
	ReziseDirection::SE
};

static const std::set<ReziseDirection> DownDirection{
	ReziseDirection::SE,
	ReziseDirection::S,
	ReziseDirection::SW,
};

static const std::set<ReziseDirection> LeftDirection{
	ReziseDirection::SW,
	ReziseDirection::W,
	ReziseDirection::NW,
};

void DraftPresenter::OnViewResizeSelection(const WindowDraftEditorEvent& evt)
{ // need specific handler for knowing direction move in evt
	if (!m_resizingItemAtView || // clang-format off
		(evt.EventType != window::event::WindowEventType::MouseDown &&
			evt.EventType != window::event::WindowEventType::MouseDrag ||
			m_selectionGroup->GetPositionablesCount() == 0))
	{// clang-format on
		return;
	}

	SetDraggingInfo(evt);
	// evt.DragDelta
	// evt.EventType
	// evt.KeyBoardKeys
	// evt.MouseAt
	// evt.ResizeDirection - only for WindowDraftEditorEvent. not WindowEvent

	auto currSelectionFrame = m_selectionGroup->GetFrame();

	auto& resizeDirection = evt.resizeDirection;
	auto resizingAtTop = TopDirection.contains(resizeDirection);
	auto resizingAtRight = RightDirection.contains(resizeDirection);
	auto resizingAtDown = DownDirection.contains(resizeDirection);
	auto resizingAtLeft = LeftDirection.contains(resizeDirection);
	auto movingLeftAtX = evt.DragDelta.x <= 0;
	auto movingUpAtY = evt.DragDelta.y <= 0;
	if (resizingAtTop)
	{
		currSelectionFrame.pLeftTop.y = m_dragStartAtPoint.y + evt.DragDelta.y;
		currSelectionFrame.size.height = m_selectionStartSize.height - evt.DragDelta.y;
	 }
	if (resizingAtLeft)
	{
		currSelectionFrame.pLeftTop.x = m_dragStartAtPoint.x + evt.DragDelta.x;
		currSelectionFrame.size.width = m_selectionStartSize.width - evt.DragDelta.x;
	}
	if (resizingAtRight)
	{
		currSelectionFrame.size.width = m_selectionStartSize.width + evt.DragDelta.x;
	}
	if (resizingAtDown)
	{
		currSelectionFrame.size.height = m_selectionStartSize.height + evt.DragDelta.y;
	}

	m_selectionGroup->SetFrame(currSelectionFrame);

	EmitSelectionFrameChangeSignal();

	std::cout << "Resize! " << size_t(evt.resizeDirection) << '\n';
}

// ########################################## View event handler ########################################

// ############################################## Handlers ##############################################

} // namespace app::presenter
