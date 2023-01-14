﻿#pragma once

#include "../IRectangle.h"
#include "../../ShapeSolidImpl.h"

namespace illusio::domain::shape::solid
{

class Rectangle : public ShapeSolidImpl<IRectangle>
{
public:
	using MyBase = ShapeSolidImpl<IRectangle>;

	explicit constexpr Rectangle() = default;
	explicit constexpr Rectangle(const PointD& basePoint, const SizeD& size, StylePtr&& outlineStyle, StylePtr&& fillColor)
		: MyBase(basePoint, size, std::move(outlineStyle), std::move(fillColor))
	{
	}
};

} // namespace illusio::domain::shape::solid
