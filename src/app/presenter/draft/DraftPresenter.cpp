#include "pch.h"

#include <illusio/domain/object/positionable/shape/solid/CShapeSolid/rectangle/CRectangle/Rectangle.h>
#include <illusio/domain/object/positionable/shape/solid/CShapeSolid/triangle/CTriangle/Triangle.h>
#include <illusio/domain/object/positionable/shape/solid/CShapeSolid/ellipse/CEllipse/Ellipse.h>

#include <illusio/domain/common/style/CStyle/Style.h>

#include "app/model/draft/AppModelPositionablesDraft.h"
#include "DraftPresenter.h"

namespace app::presenter
{

using IPositionableGroup = illusio::domain::IPositionableGroup;
using PositionableGroup = illusio::domain::PositionableGroup<IPositionableGroup>;

DraftPresenter::DraftPresenter(View windowDraft)
	: m_positionablesDraft(std::make_shared<model::AppModelPositionablesDraft>())
	, m_view(windowDraft)
	, m_selectionGroup(PositionableGroup::Create())
{
	if (m_view == nullptr)
	{
		throw std::logic_error("[app][presenter] DraftPresenter must be initialized with View. Null given");
	}

	m_positionablesDraft->DoOnChange(std::bind(&DraftPresenter::OnModelChange, this, std::placeholders::_1, std::placeholders::_2));
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

void DraftPresenter::OnViewLeftMouseDown(const WindowEvent& evt)
{
	if (evt.EventType != WindowEventType::MouseDown)
	{
		return;
	}

	auto pos = m_positionablesDraft->GetPositionableAtPoint(evt.MouseAt);
	if (!evt.KeyBoardKeys.contains(window::event::Keyboard::LeftCtrl))
	{
		ClearSelection();
	}
	if (pos == nullptr)
	{
		return;
	}

	m_selectionGroup->InsertPositionable(pos);

	auto posWasAtIndex = m_positionablesDraft->GetPositionableIndex(pos);
	m_positionablesDraft->MovePositionableToIndex(*posWasAtIndex, m_positionablesDraft->GetPositionablesCount());
}

void DraftPresenter::OnModelChange(ConstPositionables positionables, ConstPositionable changed)
{
	m_positionablesChangeSignal(positionables, changed);
}

} // namespace app::presenter
