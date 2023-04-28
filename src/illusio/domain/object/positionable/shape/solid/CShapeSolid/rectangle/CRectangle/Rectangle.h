#pragma once

#include "../IRectangle.h"
#include "../../ShapeSolidImpl.hpp"

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

	// <<interface>> IPositionable
	using Canvas = typename IRectangle::Canvas;
	void AddToCanvas(Canvas canvas) const final;
	// >>>>>>>>>>>>>>>>>>>>>>>>>>
};

} // namespace illusio::domain::shape::solid
