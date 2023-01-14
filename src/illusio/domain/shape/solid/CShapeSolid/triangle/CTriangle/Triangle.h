#pragma once

#include "../ITriangle.h"
#include "../../ShapeSolidImpl.h"

namespace illusio::domain::shape::solid
{

class Triangle : public ShapeSolidImpl<ITriangle>
{
public:
	using MyBase = ShapeSolidImpl<ITriangle>;

	explicit constexpr Triangle() = default;
	explicit constexpr Triangle(const PointD& basePoint, const SizeD& size, StylePtr&& outlineStyle, StylePtr&& fillColor)
		: MyBase(basePoint, size, std::move(outlineStyle), std::move(fillColor))
	{
	}

	// <<interface>> ITriangle
	PointD GetVertex1() const noexcept override;
	PointD GetVertex2() const noexcept override;
	PointD GetVertex3() const noexcept override;
	// >>>>>>>>>>>>>>>>>>>>>>>
};

} // namespace illusio::domain::shape::solid
