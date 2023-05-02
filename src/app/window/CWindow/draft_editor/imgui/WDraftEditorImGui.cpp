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
	m_draftPresenter->DoOnModelChange(std::bind(&WDraftEditorImGui::OnPresenterModelChange,
		this, std::placeholders::_1));
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
constexpr auto DEFAULT_SIZE_FOR_SHAPES = illusio::domain::common::axes::SizeD{ 100, 100 };

void WDraftEditorImGui::AddShape(ShapeType type)
{
	auto& canvasLT = m_canvas->GetLeftTop();
	auto& canvasSize = m_canvas->GetSize();
	auto center = Point{ canvasLT.x + canvasSize.x / 2 - DEFAULT_SIZE_FOR_SHAPES.width / 2 - m_scrolling.x,
		canvasLT.y + canvasSize.y / 2 - DEFAULT_SIZE_FOR_SHAPES.height / 2 - m_scrolling.y };
	m_draftPresenter->AddShape(type, center, DEFAULT_SIZE_FOR_SHAPES);
}

void WDraftEditorImGui::RemovePositionablesSelectionFromDraft()
{
	m_draftPresenter->RemovePositionablesSelection();
}

WDraftEditorImGui::CanvasSharedPtr WDraftEditorImGui::GetCanvas()
{
	return m_canvas;
}

// ############################################# Render ###############################################

constexpr ImGuiWindowFlags flags = 0 | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus;

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

void WDraftEditorImGui::RenderContent()
{
	ResetCanvas();

	AddDraftContentToCanvas();

	m_canvas->Draw();

	AddOverlay();

	HandleInput();
}

using Point = illusio::canvas::ICanvas::Point;

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

enum class MousePos
{
	LeftTop = 0,
	RightTop,
	LeftBottom,
	RightBottom,
};

MousePos GetMousePos()
{
	auto mousePos = ImGui::GetMousePos();
	const auto viewport = ImGui::GetWindowViewport();
	auto workPos = viewport->WorkPos;
	auto workSize = viewport->WorkSize;

	bool isMouseAtLeftSide = (mousePos.x < workPos.x + workSize.x / 2);
	bool isMouseAtTopSide = (mousePos.y < workPos.y + workSize.y / 2);

	return (isMouseAtLeftSide && isMouseAtTopSide) // clang-format off
		? MousePos::LeftTop
		: (isMouseAtLeftSide && !isMouseAtTopSide)
			? MousePos::LeftBottom
			: (!isMouseAtLeftSide && isMouseAtTopSide)
				? MousePos::RightTop
				: MousePos::RightBottom; // clang-format on
}

void WDraftEditorImGui::AddOverlay()
{
	auto& io = ImGui::GetIO();
	auto windowFlags = // clang-format off
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_NoFocusOnAppearing |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoNav |
		ImGuiWindowFlags_NoSavedSettings; // clang-format on
	auto mousePos = GetMousePos();

	const auto PAD = 10.0f;
	const auto viewport = ImGui::GetWindowViewport();
	auto workPos = viewport->WorkPos;
	auto workSize = viewport->WorkSize;
	ImVec2 windowPos, windowPosPivot;
	auto moveAtX = (mousePos == MousePos::LeftTop || mousePos == MousePos::LeftBottom);
	auto moveAtY = (mousePos == MousePos::LeftTop || mousePos == MousePos::RightTop);
	windowPos.x = moveAtX
		? (workPos.x + workSize.x - PAD)
		: (workPos.x + PAD);
	windowPos.y = moveAtY
		? (workPos.y + workSize.y - PAD)
		: (workPos.y + PAD);
	windowPosPivot.x = moveAtX
		? 1.0f
		: 0.0f;
	windowPosPivot.y = moveAtY
		? 1.0f
		: 0.0f;
	ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always, windowPosPivot);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
	if (ImGui::Begin("##", nullptr, windowFlags))
	{
		if (ImGui::IsMousePosValid())
			ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x - m_scrolling.x, io.MousePos.y - m_scrolling.y);
		else
			ImGui::Text("Mouse Position: <invalid>");
	}
	ImGui::End();
}

// ############################################# Render ###############################################

// ######################################### Mouse Handling ###########################################

void WDraftEditorImGui::HandleMouseCursorStyle()
{
	static auto DEFAULT_MOUSE_CURSOR = ImGui::GetMouseCursor();

	auto mousePos = ImGui::GetMousePos();

	if (m_draftPresenter->IsPointHoversPositionable(Point{ mousePos.x - m_scrolling.x, mousePos.y - m_scrolling.y }))
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	}
	else
	{
		ImGui::SetMouseCursor(DEFAULT_MOUSE_CURSOR);
	}
}

void WDraftEditorImGui::HandleMouseInput()
{
	HandleMouseLeftButton();
	HandleMouseRightButton();
}

void WDraftEditorImGui::HandleMouseLeftButton()
{
	auto pos = ImGui::GetMousePos();

	if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
	{

		auto windowEvent = event::WindowEvent{};
		windowEvent.EventType = event::WindowEventType::MouseDown;
		windowEvent.MouseAt = Point{ pos.x - m_scrolling.x, pos.y - m_scrolling.y };

		if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl))
		{
			windowEvent.KeyBoardKeys.insert(event::Keyboard::LeftCtrl);
		}

		EmitWindowEvent(windowEvent);
	}

	if (ImGui::IsMouseDragging(ImGuiMouseButton_Left))
	{
		auto dragDelta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Left);
		auto windowEvent = event::WindowEvent{};
		windowEvent.EventType = event::WindowEventType::MouseDrag;
		windowEvent.MouseAt = Point{ pos.x - m_scrolling.x, pos.y - m_scrolling.y };
		windowEvent.DragDelta = Point{ dragDelta.x, dragDelta.y };

		EmitWindowEvent(windowEvent);
	}
}

void WDraftEditorImGui::HandleMouseRightButton()
{
	ImGuiIO& io = ImGui::GetIO();
	auto draggingByRightMouseBtn = ImGui::IsMouseDragging(ImGuiMouseButton_Right);
	if (draggingByRightMouseBtn)
	{
		m_scrolling.x += io.MouseDelta.x;
		m_scrolling.y += io.MouseDelta.y;
	}
}

// ######################################### Mouse Handling ###########################################

// ########################################### Handlers ###############################################

void WDraftEditorImGui::HandleInput()
{
	ImVec2 canvasSize{ float(m_canvas->GetSize().x), float(m_canvas->GetSize().y) };
	ImVec2 canvasLeftTopPoint{ float(m_canvas->GetLeftTop().x), float(m_canvas->GetLeftTop().y) };

	ImGui::InvisibleButton("canvas", canvasSize, ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);
	const bool is_active = ImGui::IsItemActive();

	if (is_active)
	{
		HandleMouseInput();
	}

	HandleMouseCursorStyle();
}

void WDraftEditorImGui::OnPresenterModelChange(const DomainPositionableModelEvent& evt)
{
	m_modelSnapshot = evt.PositionablesGroup;
}

// ########################################### Handlers ###############################################

} // namespace app::window
