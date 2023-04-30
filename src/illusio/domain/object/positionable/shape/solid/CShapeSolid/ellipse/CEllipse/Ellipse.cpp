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

bool Ellipse::IsPositionableContainsPoint(const PointD& point) const noexcept
{
	auto frame = GetFrame();
	auto& size = frame.size;
	auto& pLT = frame.pLeftTop;
	auto ellipseCenter = Point{ pLT.x + size.width / 2, pLT.y + size.height / 2 };

	return CheckPointInsideOfEllipse(point, ellipseCenter, size) <= 1.0;
}

void Ellipse::AddToCanvas(Canvas canvas) const
{
	MyBase::AddToCanvas(canvas);

	auto frame = GetFrame();
	auto& pLT = frame.pLeftTop;
	auto& size = frame.size;
	auto pRB = PointD{ pLT.x + size.width, pLT.y + size.height };

	auto fillColor = GetFillColor().GetColor();
	auto outlineColor = GetOutlineStyle().GetColor();

	canvas->AddFilledEllipse(pLT, pRB, fillColor, outlineColor, 1);
}

} // namespace illusio::domain::shape::solid
