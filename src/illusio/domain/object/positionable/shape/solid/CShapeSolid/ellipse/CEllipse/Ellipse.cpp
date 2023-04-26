#include "pch_illusio.h"

#include "Ellipse.h"

namespace illusio::domain::shape::solid
{

using Point = Ellipse::PointD;
using Size = Ellipse::SizeD;

double CheckPointInsideOfEllipse(const Point& p, const Point& ellipseCenter, const Size& ellipseSize)
{
	double res = (std::pow((p.x - ellipseCenter.x), 2) / std::pow(ellipseSize.width / 2, 2))
		+ (std::pow((p.y - ellipseCenter.y), 2) / std::pow(ellipseSize.height / 2, 2));

	return res;
}

Ellipse::UuidOpt Ellipse::GetUuidOfPositionableAtPoint(const PointD& point)
{
	auto frame = GetFrame();
	auto& size = frame.size;
	auto& pLT = frame.pLeftTop;
	auto ellipseCenter = Point{ pLT.x + size.width / 2, pLT.y + size.height / 2 };

	if (CheckPointInsideOfEllipse(point, ellipseCenter, size) <= 1.0)
	{
		return GetUuid();
	}

	return std::nullopt;
}

void Ellipse::DrawAtCanvas(Canvas canvas) const
{
	MyBase::DrawAtCanvas(canvas);

	auto frame = GetFrame();
	auto& pLT = frame.pLeftTop;
	auto& size = frame.size;
	auto pRB = PointD{ pLT.x + size.width, pLT.y + size.height };

	auto fillColor = GetFillColor().GetColor();
	auto outlineColor = GetOutlineStyle().GetColor();

	canvas->AddFilledEllipse(pLT, pRB, fillColor, outlineColor, 1);
}

} // namespace illusio::domain::shape::solid
