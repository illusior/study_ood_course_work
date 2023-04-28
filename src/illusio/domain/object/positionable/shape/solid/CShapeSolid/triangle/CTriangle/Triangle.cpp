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
		frame.pLeftTop.y
	};
}

Triangle::PointD Triangle::GetVertex3() const noexcept
{
	auto frame = GetFrame();
	return PointD{
		frame.pLeftTop.x + frame.size.width,
		frame.pLeftTop.y + frame.size.height
	};
}

using PointD = Triangle::PointD;

double Sign(const PointD& p1, const PointD& p2, const PointD& p3)
{
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool PointInTriangle(const PointD& pt, const PointD& v1, const PointD& v2, const PointD& v3)
{
	double d1, d2, d3;
	bool has_neg, has_pos;

	d1 = Sign(pt, v1, v2);
	d2 = Sign(pt, v2, v3);
	d3 = Sign(pt, v3, v1);

	has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(has_neg && has_pos);
}

Triangle::UuidOpt Triangle::GetUuidOfPositionableAtPoint(const PointD& point)
{
	if (PointInTriangle(point, GetVertex1(), GetVertex2(), GetVertex3()))
	{
		return GetUuid();
	}

	return std::nullopt;
}

void Triangle::AddToCanvas(Canvas canvas) const
{
	MyBase::AddToCanvas(canvas);

	auto frame = GetFrame();
	auto& size = frame.size;
	auto& pLT = frame.pLeftTop;
	auto pRB = PointD{ pLT.x + size.width, pLT.y + size.height };

	auto v1 = GetVertex1();
	auto v2 = GetVertex2();
	auto v3 = GetVertex3();

	canvas->AddTriangleFilled(v1, v2, v3, GetFillColor().GetColor());
	canvas->AddPolyline({ v1, v2, v3 }, GetOutlineStyle().GetColor(), 1);
}

} // namespace illusio::domain::shape::solid
