﻿#pragma once

#include <functional>
#include <optional>

#include <illusio/common/signals/signal.hpp>

#include <illusio/domain/common/frame/CFrame/FrameD.h>
#include <illusio/domain/common/point/CPoint/PointD.h>
#include <illusio/domain/common/size/CSize/SizeD.h>
#include <illusio/domain/object/positionable/IPositionable.h>
#include <illusio/domain/object/positionable/group/IPositionableGroup.h>
#include <illusio/domain/object/positionable/shape/ShapeTypes.h>

#include "IPositionablesDraftPresenter_fwd.h"

namespace app::presenter
{

class IPositionablesDraftPresenter
{
public:
	using ShapeType = illusio::domain::shape::ShapeType;
	using Point = illusio::domain::common::axes::PointD;
	using Size = illusio::domain::common::axes::SizeD;
	virtual void AddShape(ShapeType shapeType, const Point& startPoint, const Size& size) = 0;

	virtual void RemovePositionablesSelection() = 0;

	virtual bool IsPointHoversPositionable(const Point& p) const noexcept = 0;

	using Connection = illusio::common::connection;
	using DomainPositionableModelEvent = illusio::domain::IPositionable::DomainPositionableModelEvent;
	using OnModelChangeCallback = std::function<void(const DomainPositionableModelEvent&)>;
	virtual Connection DoOnModelChange(const OnModelChangeCallback& handler) = 0;

	using FrameOpt = std::optional<illusio::domain::common::axes::FrameD>;
	using OnSelectionFrameChangeCallback = std::function<void(const FrameOpt&)>;
	virtual Connection DoOnSelectionFrameChange(const OnSelectionFrameChangeCallback& handler) = 0;

	virtual ~IPositionablesDraftPresenter() = default;
};

} // namespace app::presenter
