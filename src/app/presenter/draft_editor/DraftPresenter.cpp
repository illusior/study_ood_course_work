#include "pch.h"

#include <illusio/domain/object/positionable/group/CPositionableGroup/PositionablesDraft.h>
#include <illusio/domain/object/positionable/shape/solid/CShapeSolid/rectangle/CRectangle/Rectangle.h>
#include <illusio/domain/object/positionable/shape/solid/CShapeSolid/triangle/CTriangle/Triangle.h>
#include <illusio/domain/object/positionable/shape/solid/CShapeSolid/ellipse/CEllipse/Ellipse.h>

#include <illusio/domain/common/style/CStyle/Style.h>

#include "DraftPresenter.h"

namespace app::presenter
{

DraftPresenter::DraftPresenter(View windowDraft)
	: m_positionableDraft(std::make_shared<illusio::domain::PositionablesDraft>())
	, m_view(windowDraft)
{
	if (m_view == nullptr)
	{
		throw std::logic_error("[app][presenter] DraftPresenter must be initialized with View. Null given");
	}
	m_view->OnScrollingChange(std::bind(&DraftPresenter::DoOnViewScrolling, this, std::placeholders::_1));
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
	// m_undoManager.
	AddShapeToDraft(m_positionableDraft.get(), shapeType, startPoint, size);
}

DraftPresenter::IDocument::PositionableGroup DraftPresenter::GetPositionableGroup() const
{
	return m_positionableDraft->GetPositionableGroup();
}

DraftPresenter::UuidOpt DraftPresenter::GetUuidOfPositionableAtPoint(const Point& p)
{
	return m_positionableDraft->GetUuidOfPositionableAtPoint(p);
}

void DraftPresenter::SelectPositionable(const UuidOpt& uuid)
{
	m_positionableDraft->SelectPositionable(uuid);
}

const DraftPresenter::FrameOpt& DraftPresenter::GetSelectionFrame() const noexcept
{
	return m_positionableDraft->GetSelectionFrame();
}

bool DraftPresenter::CanUndo() const noexcept
{
	return m_undoManager.CanUndo();
}

bool DraftPresenter::CanRedo() const noexcept
{
	return m_undoManager.CanRedo();
}

void DraftPresenter::DoOnViewScrolling(const ImVec2& scroll)
{
	auto positionablesCount = m_positionableDraft->GetPositionablesCount();
	for (size_t i = 0; i < positionablesCount; ++i)
	{
		auto positionable = m_positionableDraft->GetPositionable(i);
		auto newFrame = positionable->GetFrame();
		newFrame.pLeftTop.x += scroll.x;
		newFrame.pLeftTop.y += scroll.y;

		positionable->SetFrame(newFrame);
	}
}

} // namespace app::presenter
