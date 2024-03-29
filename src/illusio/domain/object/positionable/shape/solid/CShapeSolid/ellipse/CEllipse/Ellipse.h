﻿#pragma once

#include "../IEllipse.h"
#include "../../ShapeSolidImpl.hpp"

namespace illusio::domain::shape::solid
{

class Ellipse : public ShapeSolidImpl<IEllipse>
{
public:
	using MyBase = ShapeSolidImpl<IEllipse>;

	explicit constexpr Ellipse() = default;
	explicit constexpr Ellipse(const PointD& basePoint, const SizeD& size, StylePtr&& outlineStyle, StylePtr&& fillColor)
		: MyBase(basePoint, size, std::move(outlineStyle), std::move(fillColor))
	{
	}

	// <<interface>> IPositionable
	bool IsPositionableContainsPoint(const PointD& point) const noexcept final;

	void AddToCanvas(Canvas canvas) const final;
	// >>>>>>>>>>>>>>>>>>>>>>>>>>>

	// <<interface>> IEllipse
	// >>>>>>>>>>>>>>>>>>>>>>>
};

} // namespace illusio::domain::shape::solid
