#include "pch_illusio.h"

#include "Triangle.h"

namespace illusio::domain::shape::solid
{

Triangle::PointD Triangle::GetVertex1() const noexcept
{
	auto frame = GetFrame();
	return PointD{
		frame.pLeftTop.x,
		frame.pLeftTop.y + frame.size.height
	};
}

Triangle::PointD Triangle::GetVertex2() const noexcept
{
	auto frame = GetFrame();
	return PointD{
		frame.pLeftTop.x + frame.size.width / 2,
		frame.pLeftTop.y + frame.size.height / 2
	};
}

Triangle::PointD Triangle::GetVertex3() const noexcept
{
	auto frame = GetFrame();
	return PointD{
		frame.pLeftTop.x + frame.size.width,
		frame.pLeftTop.y
	};
}

} // namespace illusio::domain::shape::solid
