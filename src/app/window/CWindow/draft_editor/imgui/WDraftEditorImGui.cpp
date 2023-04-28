#include "pch.h"

#include <app/presenter/draft_editor/DraftPresenter.h>
#include <illusio/canvas/CCanvas/imgui/CanvasImGui.h>
#include <illusio/domain/common/size/CSize/SizeD.h>
#include <libfastsignals/include/signal.h>

#include "WDraftEditorImGui.h"

namespace app::window
{

constexpr auto TITLE = "Draft Editor";

WDraftEditorImGui::WDraftEditorImGui()
	: MyBase(TITLE)
	, m_canvas(std::make_shared<illusio::canvas::CanvasImGui>())
	, m_draftPresenter(std::make_unique<app::presenter::DraftPresenter>(this))
{
}

constexpr ImGuiWindowFlags flags = 0 | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

bool WDraftEditorImGui::Begin()
{
	// dynamic window resize adjusting
	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);

	return IsOpen() && ImGui::Begin(m_title.data(), &m_hasCloseButton, flags);
}

void WDraftEditorImGui::End()
{
	ImGui::End();
}

WDraftEditorImGui::CanvasRenderingBoundInfo WDraftEditorImGui::GetCanvasRendernBoundInfo() const
{
	auto pLT = ImGui::GetCursorScreenPos(); // pointLeftTop
	auto size = ImGui::GetContentRegionAvail();
	auto pRB = ImVec2(pLT.x + size.x, pLT.y + size.y);

	return { pLT, pRB, size };
}

bool WDraftEditorImGui::IsGridEnabled() noexcept
{
	return m_isGridEnabled;
}

void WDraftEditorImGui::ToggleGrid() noexcept
{
	m_isGridEnabled = !m_isGridEnabled;
}

using Point = illusio::domain::common::axes::PointD;
const auto DEFAULT_SIZE_FOR_SHAPES = illusio::domain::common::axes::SizeD{ 100, 100 };

void WDraftEditorImGui::AddShape(ShapeType type)
{
	auto& canvasLT = m_canvas->GetLeftTop();
	auto& canvasSize = m_canvas->GetSize();
	auto center = Point{ canvasLT.x + canvasSize.x / 2 - DEFAULT_SIZE_FOR_SHAPES.width / 2 - m_scrolling.x,
		canvasLT.y + canvasSize.y / 2 - DEFAULT_SIZE_FOR_SHAPES.height / 2 - m_scrolling.y};
	m_draftPresenter->AddShape(type, center, DEFAULT_SIZE_FOR_SHAPES);
}

WDraftEditorImGui::CanvasSharedPtr WDraftEditorImGui::GetCanvas()
{
	return m_canvas;
}

using Point = illusio::canvas::ICanvas::Point;

void WDraftEditorImGui::AddDraftGridToCanvas()
{
	if (!m_isGridEnabled)
	{
		return;
	}

	auto canvasLeftTopPoint = ImVec2{ float(m_canvas->GetLeftTop().x), float(m_canvas->GetLeftTop().y) };
	auto& canvasSize = m_canvas->GetSize();
	auto canvasRightBottomPoint = ImVec2{ float(canvasLeftTopPoint.x + canvasSize.x), float(canvasLeftTopPoint.y + canvasSize.y) };

	if (m_isGridEnabled)
	{
		for (float x = fmodf(m_scrolling.x, m_gridStep); x < canvasSize.x; x += m_gridStep)
		{
			m_canvas->AddLine(Point{ canvasLeftTopPoint.x + x, 0.0f },
				Point{ canvasLeftTopPoint.x + x, canvasLeftTopPoint.y + canvasRightBottomPoint.y },
				m_gridColor);
		}
		for (float y = fmodf(m_scrolling.y, m_gridStep); y < canvasSize.y; y += m_gridStep)
		{
			m_canvas->AddLine(Point{ 0.0f, canvasLeftTopPoint.y + y },
				Point{ canvasLeftTopPoint.x + canvasRightBottomPoint.x, canvasLeftTopPoint.y + y },
				m_gridColor);
		}
	}
}

void WDraftEditorImGui::ResetCanvas()
{
	m_canvas->Clear();
	m_canvas->SetOrigin(Point{ 0, 0 });

	auto [canvasLeftTopPoint, canvasRightBottomPoint, canvasSize] = GetCanvasRendernBoundInfo();

	m_canvas->SetLeftTop(Point{ canvasLeftTopPoint.x, canvasLeftTopPoint.y });
	m_canvas->SetSize(Point{ canvasSize.x, canvasSize.y });

	// add backround
	m_canvas->AddRectFilled(Point{ 0, 0 },
		Point{ canvasLeftTopPoint.x + canvasRightBottomPoint.x, canvasLeftTopPoint.y + canvasRightBottomPoint.y }, m_backgroundColor);

	AddDraftGridToCanvas();
}

void WDraftEditorImGui::HandleInput()
{
	ImVec2 canvasSize{ float(m_canvas->GetSize().x), float(m_canvas->GetSize().y) };
	ImVec2 canvasLeftTopPoint{ float(m_canvas->GetLeftTop().x), float(m_canvas->GetLeftTop().y) };

	ImGui::InvisibleButton("canvas", canvasSize, ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);
	// const bool is_hovered = ImGui::IsItemHovered();
	const bool is_active = ImGui::IsItemActive();
	ImGuiIO& io = ImGui::GetIO();

	if (is_active)
	{
		auto draggingByRightMouseBtn = ImGui::IsMouseDragging(ImGuiMouseButton_Right);

		if (draggingByRightMouseBtn)
		{
			m_scrolling.x += io.MouseDelta.x;
			m_scrolling.y += io.MouseDelta.y;
		}

		if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
		{
			auto pos = ImGui::GetMousePos();
			/*std::cout << "x: " << pos.x << " y: " << pos.y << "\n";
			std::cout << "scrolling x: " << m_scrolling.x << " y: " << m_scrolling.y << "\n";*/
			auto uuidO = m_draftPresenter->GetUuidOfPositionableAtPoint(Point{ pos.x - m_scrolling.x, pos.y - m_scrolling.y });
			m_draftPresenter->SelectPositionable(uuidO);

			/*std::cout << "id1\n";
			if (uuidO.has_value())
			{
				std::cout << uuidO->data << '\n';
			}
			else
			{
				std::cout << "no" << '\n';
			}*/
		}
	}
}

void WDraftEditorImGui::RenderContent()
{
	ResetCanvas();

	const auto& selectionFrameO = m_draftPresenter->GetSelectionFrame();
	if (selectionFrameO.has_value())
	{
		auto& frame = *selectionFrameO;
		std::cout << "Frame: lt x: " << frame.pLeftTop.x << " y: " << frame.pLeftTop.y << '\n';
	}
	else
	{
		std::cout << "NO FRAME" << '\n';
	}

	HandleInput();

	m_canvas->SetOrigin(Point{ m_scrolling.x, m_scrolling.y });

	auto pos = m_draftPresenter->GetPositionableGroup();
	pos->AddToCanvas(m_canvas.get());

	m_canvas->Draw();
}

} // namespace app::window
