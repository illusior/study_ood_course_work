#pragma once

#include <functional>
#include <vector>

#include <imgui/imgui.h>

#include "../../ICanvas.h"

namespace illusio::canvas
{

class CanvasImGui : public ICanvas
{
public:
	explicit CanvasImGui() = default;

	// <<interface>> ICanvas
	void AddFilledPolygon(const Points& points, const Color& color) final;
	void AddLine(const Point& p1, const Point& p2, const Color& color) final;
	void AddPolyline(const Points& points, const Color& color, double thikness) final;
	void AddFilledEllipse(const Point& topLeft, const Point& bottomRight, const Color& fillColor, const Color& borderColor, double thikness) final;
	void AddRectFilled(const Point& p1, const Point& p2, const Color& color) final;
	void AddTriangleFilled(const Point& p1, const Point& p2, const Point& p3, const Color& color) final;

	void Draw() final;
	void Clear() final;

	void SetLeftTop(const Point& leftTop) final;
	void SetOrigin(const Point& p) final;
	void SetSize(const Size& size) final;

	const Point& GetLeftTop() noexcept final;
	const Point& GetOrigin() noexcept final;
	const Point& GetRightBottom() noexcept final;
	const Size& GetSize() noexcept final;
	// >>>>>>>>>>>>>>>>>>>>>

private:
	Point m_origin, m_leftTop, m_rightBottom;
	Size m_size;

	using DrawAction = std::function<void()>;
	using DrawActionSequence = std::vector<DrawAction>;
	DrawActionSequence m_drawingsSequence;
};

} // namespace illusio::canvas
