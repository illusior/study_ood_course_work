#pragma once

#include <vector>

#include "ICanvas_fwd.h"

#include "domain/common/color/RGBAColor.h"
#include "domain/common/point/CPoint/PointD.h"

namespace illusio::canvas
{

class ICanvas
{
public:
	using Point = domain::common::axes::PointD;
	using Points = std::vector<Point>;
	using Size = Point;
	using Color = domain::common::color::RGBAColor;

	virtual void SetLeftTop(const Point& leftTop) = 0;
	virtual void SetSize(const Size& size) = 0;
	virtual const Point& GetLeftTop() noexcept = 0;
	virtual const Size& GetSize() noexcept = 0;

	virtual void AddFilledPolygon(const Points& points, const Color& color) = 0;
	virtual void AddLine(const Point& p1, const Point& p2, const Color& color) = 0;
	virtual void AddPolyline(const Points& points, const Color& color, double thikness) = 0;
	virtual void AddFilledEllipse(const Point& topLeft, const Point& bottomRight, const Color& fillColor, const Color& borderColor, double thikness) = 0;
	virtual void AddRectFilled(const Point& p1, const Point& p2, const Color& color) = 0;
	virtual void AddTriangleFilled(const Point& p1, const Point& p2, const Point& p3, const Color& color) = 0;

	virtual void Draw() = 0;
	virtual void Clear() = 0;

	virtual ~ICanvas() = default;
};

} // namespace illusio::canvas
