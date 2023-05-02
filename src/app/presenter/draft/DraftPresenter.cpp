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

	m_positionablesDraft->DoOnChange(std::bind(&DraftPresenter::OnModelChange, this, std::placeholders::_1));
	m_view->DoOnFiringWindowEvent(std::bind(&DraftPresenter::OnViewLeftMouseDragging, this, std::placeholders::_1));
	m_view->DoOnFiringWindowEvent(std::bind(&DraftPresenter::OnViewKeyboardDown, this, std::placeholders::_1));
	m_view->DoOnFiringWindowEvent(std::bind(&DraftPresenter::OnViewLeftMouseDown, this, std::placeholders::_1));
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

DraftPresenter::FrameOpt DraftPresenter::GetSelectionFrame() const
{
	return m_selectionGroup->GetFrame();
}

DraftPresenter::Connection DraftPresenter::DoOnModelChange(const OnModelChangeCallback& callback)
{
	return m_positionablesChangeSignal.connect(callback);
}

void DraftPresenter::ClearSelection()
{
	auto posCount = m_selectionGroup->GetPositionablesCount();
	if (posCount == 0)
	{
		return;
	}

	for (; posCount > 0; --posCount)
	{
		m_selectionGroup->RemovePositionable(posCount - 1);
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
}

bool DraftPresenter::IsPointHoversPositionable(const Point& p) const noexcept
{
	return bool(m_positionablesDraft->GetPositionableAtPoint(p));
}

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
		return;
	}

	auto posIndexInSelection = m_selectionGroup->GetPositionableIndex(pos);
	auto isPosInSelection = posIndexInSelection.has_value();
	if (collectingButtonPressed && isPosInSelection)
	{
		m_selectionGroup->RemovePositionable(*posIndexInSelection);
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

	MoveSelectionToTop();
}

void DraftPresenter::MoveSelectionToTop()
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

void DraftPresenter::OnViewLeftMouseDragging(const WindowEvent& evt)
{
	if (evt.EventType != window::event::WindowEventType::MouseDrag || m_selectionGroup->GetPositionablesCount() == 0)
	{
		m_dragging = false;
		m_dragStartAtPoint_leftTopSelection_delta = Point{};
		m_dragStartAtPoint = Point{};
		return;
	}

	auto currSelectionFrame = m_selectionGroup->GetFrame();
	
	// new value of currSelectionFrame's pLeftTop must NOT be recurrent, otherwise you'll see flickering selection
	if (!m_dragging)
	{
		m_dragStartAtPoint = Point{
			evt.MouseAt.x,
			evt.MouseAt.y
		};
		m_dragStartAtPoint_leftTopSelection_delta = Point{
			evt.MouseAt.x - currSelectionFrame.pLeftTop.x,
			evt.MouseAt.y - currSelectionFrame.pLeftTop.y
		};
		m_dragging = true;
	}
	currSelectionFrame.pLeftTop.x = m_dragStartAtPoint.x + evt.DragDelta.x - m_dragStartAtPoint_leftTopSelection_delta.x;
	currSelectionFrame.pLeftTop.y = m_dragStartAtPoint.y + evt.DragDelta.y - m_dragStartAtPoint_leftTopSelection_delta.y;

	m_selectionGroup->SetFrame(currSelectionFrame);
}

// ########################################## View event handler ########################################

} // namespace app::presenter
