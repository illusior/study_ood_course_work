#include "pch.h"

#include <app/presenter/draft/DraftPresenter.h>
#include <illusio/canvas/CCanvas/imgui/CanvasImGui.h>
#include <illusio/domain/common/size/CSize/SizeD.h>

#include "WDraftEditorImGui.h"

namespace app::window
{

constexpr auto TITLE = "Draft Editor";

WDraftEditorImGui::WDraftEditorImGui()
	: MyBase(TITLE)
	, m_canvas(std::make_shared<illusio::canvas::CanvasImGui>())
	, m_draftPresenter(std::make_unique<app::presenter::DraftPresenter>(this))
	, m_modelSnapshot(nullptr)
{
	m_draftPresenter->DoOnModelChange(std::bind(&WDraftEditorImGui::OnPresenterModelChange, this, std::placeholders::_1, std::placeholders::_2));
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
		canvasLT.y + canvasSize.y / 2 - DEFAULT_SIZE_FOR_SHAPES.height / 2 - m_scrolling.y };
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

			auto windowEvent = event::WindowEvent{};
			windowEvent.EventType = event::WindowEventType::MouseDown;
			windowEvent.MouseAt = Point{ pos.x - m_scrolling.x, pos.y - m_scrolling.y };

			if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl))
			{
				windowEvent.KeyBoardKeys.insert(event::Keyboard::LeftCtrl);
			}

			EmitWindowEvent(windowEvent);
		}
	}
}

void WDraftEditorImGui::OnPresenterModelChange(ModelSnapshot newSnapshot, ChangedValue newValue)
{
	m_modelSnapshot = newSnapshot;
}

void WDraftEditorImGui::AddDraftContentToCanvas()
{
	if (m_modelSnapshot == nullptr)
	{
		return;
	}

	m_canvas->SetOrigin(Point{ m_scrolling.x, m_scrolling.y });
	m_modelSnapshot->AddToCanvas(m_canvas.get());

	AddSelectionFrameToCanvas();
}

void WDraftEditorImGui::AddSelectionFrameToCanvas()
{
	auto selectionFrameOpt = m_draftPresenter->GetSelectionFrame();

	if (!selectionFrameOpt.has_value())
	{
		return;
	}

	auto& selectionFrame = *selectionFrameOpt;
	auto& size = selectionFrame.size;

	auto frameLT = selectionFrame.pLeftTop;
	auto frameRT = Point{ frameLT.x + size.width, frameLT.y };
	auto frameRB = Point{ frameLT.x + size.width, frameLT.y + size.height };
	auto frameLB = Point{ frameLT.x, frameLT.y + size.height };

	m_canvas->AddPolyline({ frameLT, frameRT, frameRB, frameLB }, m_selectionFrameColor, m_selectionFrameThikness);
}

void WDraftEditorImGui::RenderContent()
{
	ResetCanvas();

	HandleInput();

	AddDraftContentToCanvas();

	m_canvas->Draw();
}

} // namespace app::window
