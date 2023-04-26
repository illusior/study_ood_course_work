#include "pch_illusio.h"

#include "CanvasImGui.h"

namespace illusio::canvas
{

void CanvasImGui::SetLeftTop(const Point& leftTop)
{
	m_leftTop = leftTop;
}

void CanvasImGui::SetSize(const Size& size)
{
	m_size = size;
}

const CanvasImGui::Point& CanvasImGui::GetLeftTop() noexcept
{
	return m_leftTop;
}

const CanvasImGui::Size& CanvasImGui::GetSize() noexcept
{
	return m_size;
}

using ImGuiPoints = std::vector<ImVec2>;
ImGuiPoints TranslateToImGuiPoints(const CanvasImGui::Points& points)
{
	ImGuiPoints result{};
	result.reserve(points.size());

	for (auto& p : points)
	{
		result.emplace_back(float(p.x), float(p.y));
	}

	return result;
}

void CanvasImGui::AddFilledPolygon(const std::vector<Point>& points, const Color& color)
{
	m_drawingsSequence.push_back([points, imDrawList = ImGui::GetWindowDrawList(), color]() {
		auto imGuiPoints = TranslateToImGuiPoints(points);

		imDrawList->AddConvexPolyFilled(imGuiPoints.data(), imGuiPoints.size(), color);
	});
}

void CanvasImGui::AddLine(const Point& p1, const Point& p2, const Color& color)
{
	m_drawingsSequence.push_back([p1, p2, imDrawList = ImGui::GetWindowDrawList(), color]() {
		imDrawList->AddLine(ImVec2(float(p1.x), float(p1.y)), ImVec2(float(p2.x), float(p2.y)), color);
	});
}

void CanvasImGui::AddPolyline(const std::vector<Point>& points, const Color& color, double thikness)
{
	m_drawingsSequence.push_back([points, imDrawList = ImGui::GetWindowDrawList(), color, thikness]() {
		auto imGuiPoints = TranslateToImGuiPoints(points);

		imDrawList->AddPolyline(imGuiPoints.data(),
			imGuiPoints.size(), color, ImDrawFlags_Closed, float(thikness));
	});
}

void CanvasImGui::AddFilledEllipse(const Point& topLeft, const Point& bottomRight, const Color& fillColor, const Color& borderColor, double thikness)
{
	static const float doublePi = 2.0f * M_PI;
	const float
		cx = (topLeft.x + bottomRight.x) / 2,
		cy = (topLeft.y + bottomRight.y) / 2,
		w = (bottomRight.x - topLeft.x) / 2,
		h = (bottomRight.y - topLeft.y) / 2;
	std::vector<ImVec2> points;
	auto imDrawList = ImGui::GetWindowDrawList();
	auto pointsNum = imDrawList->_CalcCircleAutoSegmentCount(std::max(w, h));
	for (float a = 0.0f; a <= doublePi; a += (doublePi / pointsNum))
	{
		const float x = cx + cos(a) * w;
		const float y = cy + sin(a) * h;
		points.push_back(ImVec2(x, y));
	}
	m_drawingsSequence.push_back([imDrawList, points, fillColor, borderColor, thikness]() {
		imDrawList->AddConvexPolyFilled(points.data(), points.size(), fillColor);
		imDrawList->AddPolyline(points.data(), points.size(),
			borderColor, ImDrawFlags_Closed, thikness);
	});
}

void CanvasImGui::AddRectFilled(const Point& p1, const Point& p2, const Color& color)
{
	m_drawingsSequence.push_back([p1, p2, imDrawList = ImGui::GetWindowDrawList(), color]() {
		auto imGuiPoints = TranslateToImGuiPoints({ p1, p2 });
		imDrawList->AddRectFilled(imGuiPoints[0], imGuiPoints[1], color);
	});
}

void CanvasImGui::AddTriangleFilled(const Point& p1, const Point& p2, const Point& p3, const Color& color)
{
	m_drawingsSequence.push_back([p1, p2, p3, imDrawList = ImGui::GetWindowDrawList(), color]() {
		auto imGuiPoints = TranslateToImGuiPoints({ p1, p2, p3 });

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

} // namespace illusio::canvas
