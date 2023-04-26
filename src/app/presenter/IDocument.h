#pragma once

#include <illusio/domain/common/point/CPoint/PointD.h>
#include <illusio/domain/common/size/CSize/SizeD.h>
#include <illusio/domain/object/positionable/IPositionable.h>
#include <illusio/domain/object/positionable/group/IPositionableGroup.h>
#include <illusio/domain/object/positionable/shape/ShapeTypes.h>

#include "IDocument_fwd.h"

namespace app::presenter
{

class IDocument
{
public:
	using ShapeType = illusio::domain::shape::ShapeType;
	using Point = illusio::domain::common::axes::PointD;
	using Size = illusio::domain::common::axes::SizeD;
	virtual void AddShape(ShapeType shapeType, const Point& startPoint, const Size& size) = 0;

	using PositionableGroup = illusio::domain::IPositionableGroupSharedConstPtr;
	virtual PositionableGroup GetPositionableGroup() const = 0;

	using UuidOpt = illusio::domain::IPositionable::UuidOpt;
	virtual UuidOpt GetUuidOfPositionableAtPoint(const Point& p) = 0;

	using Uuid = illusio::domain::IPositionableGroup::Uuid;
	virtual void SelectPositionable(const UuidOpt& uuid) = 0;

	using FrameOpt = illusio::domain::IPositionableGroup::FrameOpt;
	virtual const FrameOpt& GetSelectionFrame() const noexcept = 0;

	virtual bool CanUndo() const noexcept = 0;
	virtual bool CanRedo() const noexcept = 0;

	virtual ~IDocument() = default;
};

} // namespace app::presenter
