#include "pch_illusio.h"

#include "CanvasImGui.h"

namespace illusio::canvas
{

using ImGuiPoints = std::vector<ImVec2>;
ImGuiPoints TranslateToImGuiPoints(const CanvasImGui::Points& points, const CanvasImGui::Point& canvasOrigin)
{
	ImGuiPoints result{};
	result.reserve(points.size());

	for (auto& p : points)
	{
		result.emplace_back(float(p.x + canvasOrigin.x), float(p.y + canvasOrigin.y));
	}

	return result;
}

void CanvasImGui::AddFilledPolygon(const std::vector<Point>& points, const Color& color)
{
	m_drawingsSequence.push_back([points, imDrawList = ImGui::GetWindowDrawList(), color, canvasOrigin = m_origin]() {
		auto imGuiPoints = TranslateToImGuiPoints(points, canvasOrigin);

		imDrawList->AddConvexPolyFilled(imGuiPoints.data(), imGuiPoints.size(), color);
	});
}

void CanvasImGui::AddLine(const Point& p1, const Point& p2, const Color& color)
{
	m_drawingsSequence.push_back([p1, p2, imDrawList = ImGui::GetWindowDrawList(), color, canvasOrigin = m_origin]() {
		auto imGuiPoints = TranslateToImGuiPoints({ p1, p2 }, canvasOrigin);

		imDrawList->AddLine(imGuiPoints[0], imGuiPoints[1], color);
	});
}

void CanvasImGui::AddPolyline(const std::vector<Point>& points, const Color& color, double thikness)
{
	m_drawingsSequence.push_back([points, imDrawList = ImGui::GetWindowDrawList(), color, thikness, canvasOrigin = m_origin]() {
		auto imGuiPoints = TranslateToImGuiPoints(points, canvasOrigin);

		imDrawList->AddPolyline(imGuiPoints.data(),
			imGuiPoints.size(), color, ImDrawFlags_Closed, float(thikness));
	});
}

void CanvasImGui::AddFilledEllipse(const Point& topLeft, const Point& bottomRight, const Color& fillColor, const Color& borderColor, double thikness)
{
	static const float doublePi = 2.0f * M_PI;
	const float
		cx
		= (topLeft.x + bottomRight.x) / 2,
		cy = (topLeft.y + bottomRight.y) / 2,
		w = (bottomRight.x - topLeft.x) / 2,
		h = (bottomRight.y - topLeft.y) / 2;
	std::vector<ImVec2> points;
	auto imDrawList = ImGui::GetWindowDrawList();
	auto pointsNum = imDrawList->_CalcCircleAutoSegmentCount(std::max(w, h));
	points.reserve(pointsNum);
	for (float a = 0.0f; a <= doublePi; a += (doublePi / pointsNum))
	{
		const float x = cx + cos(a) * w;
		const float y = cy + sin(a) * h;
		points.push_back(ImVec2(x + float(m_origin.x), y + float(m_origin.y)));
	}
	m_drawingsSequence.push_back([imDrawList, points, fillColor, borderColor, thikness]() {
		imDrawList->AddConvexPolyFilled(points.data(), points.size(), fillColor);
		imDrawList->AddPolyline(points.data(), points.size(),
			borderColor, ImDrawFlags_Closed, thikness);
	});
}

void CanvasImGui::AddRectFilled(const Point& p1, const Point& p2, const Color& color)
{
	m_drawingsSequence.push_back([p1, p2, imDrawList = ImGui::GetWindowDrawList(), color, canvasOrigin = m_origin]() {
		auto imGuiPoints = TranslateToImGuiPoints({ p1, p2 }, canvasOrigin);
		imDrawList->AddRectFilled(imGuiPoints[0], imGuiPoints[1], color);
	});
}

void CanvasImGui::AddTriangleFilled(const Point& p1, const Point& p2, const Point& p3, const Color& color)
{
	m_drawingsSequence.push_back([p1, p2, p3, imDrawList = ImGui::GetWindowDrawList(), color, canvasOrigin = m_origin]() {
		auto imGuiPoints = TranslateToImGuiPoints({ p1, p2, p3 }, canvasOrigin);

		imDrawList->AddTriangleFilled(imGuiPoints[0], imGuiPoints[1], imGuiPoints[2], color);
	});
}

void CanvasImGui::Draw()
{
	auto copyDrawS = m_drawingsSequence;
	for (auto& drawAction : copyDrawS)
	{
		drawAction();
	}
}

void CanvasImGui::Clear()
{
	m_drawingsSequence.clear();
}

void CanvasImGui::SetOrigin(const Point& p)
{
	m_origin = p;
}

void CanvasImGui::SetLeftTop(const Point& leftTop)
{
	m_leftTop = leftTop;
}

const CanvasImGui::Point& CanvasImGui::GetLeftTop() noexcept
{
	return m_leftTop;
}

const CanvasImGui::Point& CanvasImGui::GetOrigin() noexcept
{
	return m_origin;
}

const CanvasImGui::Point& CanvasImGui::GetRightBottom() noexcept
{
	return Point{ m_leftTop.x + m_size.x, m_leftTop.y + m_size.y };
}

void CanvasImGui::SetSize(const Size& size)
{
	m_size = size;
}

const CanvasImGui::Size& CanvasImGui::GetSize() noexcept
{
	return m_size;
}

} // namespace illusio::canvas
