#include "pch_illusio.h"

#include "Rectangle.h"

namespace illusio::domain::shape::solid
{

void Rectangle::DrawAtCanvas(Canvas canvas) const
{
	MyBase::DrawAtCanvas(canvas);

	auto frame = GetFrame();
	auto& size = frame.size;
	auto& pLT = frame.pLeftTop;
	auto pRB = PointD{ pLT.x + size.width, pLT.y + size.height };

	canvas->AddRectFilled(pLT, pRB, GetFillColor().GetColor());
	canvas->AddPolyline({ pLT,
							PointD{ pRB.x, pLT.y },
							pRB, PointD{ pLT.x, pRB.y } },
		GetOutlineStyle().GetColor(),
		1);
}

} // namespace illusio::domain::shape::solid
