#pragma once

#include "../IShapeSolid.h"
#include "../../simple/ShapeImpl.hpp"

namespace illusio::domain::shape::solid
{

template <typename IBase = IShapeSolid>
class ShapeSolidImpl : public simple::ShapeImpl<IBase>
{
public:
	using MyBase = simple::ShapeImpl<IBase>;

	using Style = typename IBase::Style;
	using StylePtr = typename IBase::StylePtr;

	using PointD = typename IBase::PointD;
	using SizeD = MyBase::SizeD;

	// <<interface>> IShapeSolid
	const Style& GetFillColor() const noexcept override
	{
		return *m_fillColor;
	}
	// >>>>>>>>>>>>>>>>>>>>>>>>>

protected:
	explicit constexpr ShapeSolidImpl() = default;
	explicit constexpr ShapeSolidImpl(const PointD& basePoint, const SizeD& size, StylePtr&& outlineStyle, StylePtr&& fillColor)
		: MyBase(basePoint, size, std::move(outlineStyle))
		, m_fillColor(std::move(fillColor))
	{
	}

private:
	StylePtr m_fillColor;
};

} // namespace illusio::domain::shape::solid
