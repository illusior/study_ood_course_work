#pragma once

#include "../IShapeSolid.h"
#include "../../simple/ShapeImpl.h"

namespace illusio::domain::shape::solid
{

template <typename Base = IShapeSolid>
class ShapeSolidImpl : public simple::ShapeImpl<Base>
{
public:
	using MyBase = simple::ShapeImpl<Base>;

	using FrameD = typename MyBase::FrameD;
	using PointD = typename MyBase::PointD;
	using Style = typename MyBase::Style;
	using StylePtr = typename MyBase::StylePtr;
	using SizeD = typename MyBase::SizeD;

	// <<interface>> IShapeSolid
	const Style& GetFillColor() const noexcept final
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
