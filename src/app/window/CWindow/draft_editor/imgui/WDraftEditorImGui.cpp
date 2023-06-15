#include "pch.h"

#include <illusio/canvas/CCanvas/imgui/CanvasImGui.h>
#include <illusio/domain/common/size/CSize/SizeD.h>

#include "app/presenter/draft/DraftPresenter.h"

#include "WDraftEditorImGui.h"

namespace app::window
{

constexpr auto TITLE = "Draft Editor";

WDraftEditorImGui::WDraftEditorImGui()
	: MyBase(TITLE)
	, m_canvas(std::make_shared<illusio::canvas::CanvasImGui>())
	, m_draftPresenter(std::make_unique<app::presenter::DraftPresenter>(this))
	, m_modelSnapshot(nullptr)
	, m_resizePositionableSignal()
{
	m_draftPresenter->DoOnModelChange(std::bind(&WDraftEditorImGui::OnPresenterModelChange,
		this, std::placeholders::_1));
	m_draftPresenter->DoOnSelectionFrameChange(std::bind(&WDraftEditorImGui::OnPresenterSelectionFrameChange,
		this, std::placeholders::_1));
}

WDraftEditorImGui::CanvasRenderingBoundInfo WDraftEditorImGui::GetCanvasRendernBoundInfo() const
{
	auto pLT = ImGui::GetCursorScreenPos(); // pointLeftTop
	auto size = ImGui::GetContentRegionAvail();
	auto pRB = ImVec2(pLT.x + size.x, pLT.y + size.y);

	return { pLT, pRB, size };
}

bool WDraftEditorImGui::IsGridEnabled() const noexcept
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

WDraftEditorImGui::Connection WDraftEditorImGui::DoOnPositionableResize(const OnPositionableResizeCallback& handler)
{
	return m_resizePositionableSignal.connect(handler);
}

WDraftEditorImGui::Connection WDraftEditorImGui::DoOnDraggingResizing(const OnDraggingResizingCallback& handler)
{
	return m_resizingDraggingInfoSignal.connect(handler);
}

void WDraftEditorImGui::CalculateResizersCornerPoints()
{
	if (!m_selectionFrame.has_value())
	{
		return;
	}

	auto& selectionFrame = *m_selectionFrame;

	Points resizeMarkersPoints{};
	resizeMarkersPoints.reserve(2 * m_selectionFrameMarkersCount);

	using namespace illusio::domain::common::axes;
	FrameStrider<decltype(selectionFrame.pLeftTop.x)> frameStrider{ selectionFrame,
		m_selectionFrameMarkersCount, m_selectionFrameMarkersPadding };

	auto frameMiddleX = selectionFrame.pLeftTop.x + selectionFrame.size.width / 2;
	auto frameMiddleY = selectionFrame.pLeftTop.y + selectionFrame.size.height / 2;
	for (auto& markerAnchor : frameStrider)
	{
		auto leftHandX = markerAnchor.x < frameMiddleX;
		auto middleX = markerAnchor.x == frameMiddleX;
		auto leftHandY = markerAnchor.y < frameMiddleY;
		auto middleY = markerAnchor.y == frameMiddleY;

		auto& markerPad = m_selectionFrameMarkersPadding;
		auto offsetX = middleX
			? 0
			: leftHandX
			? -markerPad
			: markerPad;
		auto offsetY = middleY
			? 0
			: leftHandY
			? -markerPad
			: markerPad;
		resizeMarkersPoints.emplace_back(markerAnchor.x + offsetX - m_selectionFrameMarkersSize / 2,
			markerAnchor.y + offsetY - m_selectionFrameMarkersSize / 2);

		auto& markerSize = m_selectionFrameMarkersSize;
		auto& pLeftTop = resizeMarkersPoints.back();
		resizeMarkersPoints.emplace_back(pLeftTop.x + markerSize,
			pLeftTop.y + markerSize);
	}
	m_resizersOppositeCorners = resizeMarkersPoints;
}

WDraftEditorImGui::ResizeDirectionOpt WDraftEditorImGui::GetResizeDirection() const noexcept
{
	const auto& frameSelectionOpt = m_selectionFrame;
	if (!ImGui::IsMousePosValid() || !frameSelectionOpt.has_value())
	{
		return std::nullopt;
	}

	const auto mousePos = ImGui::GetMousePos();

	const auto& frameSelection = *frameSelectionOpt;
	const auto& selectionLeftTop = frameSelection.pLeftTop;
	const auto& selectionSize = frameSelection.size;
	const auto selectionMiddleX = selectionLeftTop.x + selectionSize.width / 2;
	const auto selectionMiddleY = selectionLeftTop.y + selectionSize.height / 2;

	const auto& resizerSize = m_selectionFrameMarkersSize;
	const auto selectionLeftSideWithPaddingX = selectionLeftTop.x - m_selectionFrameMarkersPadding - resizerSize;
	const auto selectionTopSideWithPaddingY = selectionLeftTop.y - m_selectionFrameMarkersPadding - resizerSize;
	const auto selectionLeftSideWithPaddingOppositeX = selectionLeftTop.x + m_selectionFrameMarkersPadding + resizerSize;
	const auto selectionTopSideWithPaddingOppositeY = selectionLeftTop.y + m_selectionFrameMarkersPadding + resizerSize;
	for (size_t i = 1, total = m_resizersOppositeCorners.size(); i < total; ++(++i))
	{
		const auto& leftTop = m_resizersOppositeCorners[i - 1];
		const auto& rightBottom = m_resizersOppositeCorners[i];

		if (auto inX = (mousePos.x >= leftTop.x && mousePos.x <= rightBottom.x),
			inY = (mousePos.y >= leftTop.y && mousePos.y <= rightBottom.y);
			inX && inY)
		{
			auto atLeftSideOfSelection = (leftTop.x >= selectionLeftSideWithPaddingX) && (leftTop.x <= selectionLeftSideWithPaddingOppositeX);
			auto atMiddleSideOfSelectionX = (leftTop.x <= selectionMiddleX && selectionMiddleX <= rightBottom.x);
			auto atTopSideOfSelection = (leftTop.y >= selectionTopSideWithPaddingY) && (leftTop.y <= selectionTopSideWithPaddingOppositeY);
			auto atMiddleSideOfSelectionY = (leftTop.y <= selectionMiddleY && selectionMiddleY <= rightBottom.y);

			if (atLeftSideOfSelection)
			{
				if (atTopSideOfSelection)
				{
					return ResizeDirection::NW;
				}
				if (atMiddleSideOfSelectionY)
				{
					return ResizeDirection::W;
				}
				return ResizeDirection::SW;
			}
			if (atMiddleSideOfSelectionX)
			{
				if (atTopSideOfSelection)
				{
					return ResizeDirection::N;
				}
				return ResizeDirection::S;
			}
			if (!atLeftSideOfSelection && !atMiddleSideOfSelectionX)
			{
				if (atTopSideOfSelection)
				{
					return ResizeDirection::NE;
				}
				if (atMiddleSideOfSelectionY)
				{
					return ResizeDirection::E;
				}
				return ResizeDirection::SE;
			}

			break;
		}
	}

	return std::nullopt;
}

void WDraftEditorImGui::OnPresenterSelectionFrameChange(const FrameOpt& frame)
{
	m_selectionFrame = frame;

	CalculateResizersCornerPoints();
}

using Frame = illusio::domain::common::axes::FrameD;

// ############################################# Render ###############################################

// clang-format off
constexpr ImGuiWindowFlags flags = 0 |
	ImGuiWindowFlags_NoTitleBar |
	ImGuiWindowFlags_NoResize |
	ImGuiWindowFlags_NoMove |
	ImGuiWindowFlags_NoBringToFrontOnFocus; // clang-format on

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

using Points = std::vector<Point>;
using Frame = illusio::domain::common::axes::FrameD;
Points GetFrameCornerPoints(const Frame& frame)
{
	auto& size = frame.size;

	auto frameLT = frame.pLeftTop;
	auto frameRT = Point{ frameLT.x + size.width, frameLT.y };
	auto frameRB = Point{ frameLT.x + size.width, frameLT.y + size.height };
	auto frameLB = Point{ frameLT.x, frameLT.y + size.height };

	return { frameLT, frameRT, frameRB, frameLB };
}

void WDraftEditorImGui::AddSelectionFrameToCanvas()
{
	auto& selectionFrameOpt = m_selectionFrame;

	if (!selectionFrameOpt.has_value())
	{
		return;
	}

	auto& selectionFrame = *selectionFrameOpt;

	m_canvas->AddPolyline(GetFrameCornerPoints(selectionFrame),
		m_selectionFrameColor, m_selectionFrameThikness);

	AddSelectionFrameResizerMarks();
}

void WDraftEditorImGui::AddSelectionFrameResizerMarks()
{
	if (!m_selectionFrame.has_value())
	{
		return;
	}

	for (size_t i = 1, total = m_resizersOppositeCorners.size(); i <= total - 1; ++(++i))
	{
		m_canvas->AddRectFilled(m_resizersOppositeCorners[i - 1],
			m_resizersOppositeCorners[i], m_selectionFrameMarekrsFillColor);
	}
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
		ImGui::SeparatorText("Input controls");

		ImGui::Text("Left mouse to select");
		ImGui::Text("   (+ LeftCtrl for multiselection)");
		ImGui::Text("Right mouse to move canvas");
		ImGui::Text("See edit tab for more");

		ImGui::SeparatorText("Mouse info");

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
	auto relMousePos = Point{ mousePos.x - m_scrolling.x, mousePos.y - m_scrolling.y };

	ImGui::SetMouseCursor(DEFAULT_MOUSE_CURSOR);
	if (m_draftPresenter->IsPointHoversPositionable(relMousePos))
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
		return;
	}

	HandleMouseCursorStyleOverResizers();
}

void WDraftEditorImGui::HandleMouseCursorStyleOverResizers()
{
	auto& selectionFrameOpt = m_selectionFrame;
	if (!selectionFrameOpt.has_value() || m_resizersOppositeCorners.size() == 0)
	{
		return;
	}

	auto mousePos = ImGui::GetMousePos();
	auto relMousePos = Point{ mousePos.x - m_scrolling.x, mousePos.y - m_scrolling.y };

	auto& selectionFrame = *selectionFrameOpt;

	auto& selectionLeftTopP = selectionFrame.pLeftTop;
	auto& selectionSize = selectionFrame.size;
	auto selectionWidthX = selectionLeftTopP.x + selectionSize.width;
	auto selectionHeightY = selectionLeftTopP.y + selectionSize.height;
	for (size_t i = 1, total = m_resizersOppositeCorners.size(); i <= total - 1; ++(++i))
	{
		auto& leftTopCorner = m_resizersOppositeCorners[i - 1];
		auto& rightBottomCorner = m_resizersOppositeCorners[i];
		auto mouseInResizerX = relMousePos.x >= leftTopCorner.x && relMousePos.x <= leftTopCorner.x + m_selectionFrameMarkersSize;
		auto mouseInResizerY = relMousePos.y >= leftTopCorner.y && relMousePos.y <= leftTopCorner.y + m_selectionFrameMarkersSize;
		auto mouseInResizer = mouseInResizerX && mouseInResizerY;

		if (mouseInResizer && (leftTopCorner.y <= selectionLeftTopP.y || rightBottomCorner.y >= selectionHeightY))
		{
			ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNS);
			return;
		}
		if (mouseInResizer && (leftTopCorner.x <= selectionLeftTopP.x || rightBottomCorner.x >= selectionWidthX))
		{
			ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
			return;
		}
	}
}

void WDraftEditorImGui::HandleMouseInput()
{
	HandleMouseLeftButtonClicked();
	HandleMouseLeftButtonDraggingOverWorkArea();
	HandleMouseRightButton();
}

void WDraftEditorImGui::HandleMouseLeftButtonClicked()
{
	if (!ImGui::IsMouseClicked(ImGuiMouseButton_Left))
	{
		m_resizingDraggingInfoSignal(false, false);
		return;
	}


	auto windowEvent = event::WindowDraftEditorEvent();
	windowEvent.EventType = event::WindowEventType::MouseDown;
	auto pos = ImGui::GetMousePos();
	windowEvent.MouseAt = Point{ pos.x - m_scrolling.x, pos.y - m_scrolling.y };

	if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl))
	{
		windowEvent.KeyBoardKeys.insert(event::Keyboard::LeftCtrl);
	}

	auto mouseAtResizerOpt = GetResizeDirection();
	auto isMouseAtResizer = mouseAtResizerOpt.has_value();
	if (isMouseAtResizer)
	{
		m_resizingDraggingInfoSignal(true, false);
		windowEvent.resizeDirection = *mouseAtResizerOpt;
		m_resizePositionableSignal(windowEvent);
	}
	else
	{
		auto isHoveringCanvasItem = m_draftPresenter->IsPointHoversPositionable(windowEvent.MouseAt);
		m_resizingDraggingInfoSignal(false, isHoveringCanvasItem);
		EmitWindowEvent(windowEvent);
	}
}

void WDraftEditorImGui::HandleMouseLeftButtonDraggingOverWorkArea()
{
	if (!ImGui::IsMouseDragging(ImGuiMouseButton_Left))
	{
		m_resizingDraggingInfoSignal(false, false);
		return;
	}

	auto pos = ImGui::GetMousePos();
	auto dragDelta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Left);

	auto windowEvent = event::WindowDraftEditorEvent();
	windowEvent.EventType = event::WindowEventType::MouseDrag;
	windowEvent.MouseAt = Point{ pos.x - m_scrolling.x, pos.y - m_scrolling.y };
	windowEvent.DragDelta = Point{ dragDelta.x, dragDelta.y };

	auto isHoveringCanvasItem = m_draftPresenter->IsPointHoversPositionable(windowEvent.MouseAt);

	m_resizingDraggingInfoSignal(false, isHoveringCanvasItem);
	EmitWindowEvent(windowEvent);
}

void WDraftEditorImGui::HandleMouseLeftButtonDraggingOverResizers()
{
	if (!ImGui::IsMouseDragging(ImGuiMouseButton_Left) && !ImGui::IsMouseDown(ImGuiMouseButton_Left))
	{
		m_resizingDraggingInfoSignal(false, false);
		return;
	}

	auto mouseAtResizerOpt = GetResizeDirection();
	if (!mouseAtResizerOpt.has_value())
	{
		return;
	}

	auto pos = ImGui::GetMousePos();
	auto dragDelta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Left);

	auto windowEvent = event::WindowDraftEditorEvent();
	windowEvent.EventType = event::WindowEventType::MouseDrag;
	windowEvent.MouseAt = Point{ pos.x - m_scrolling.x, pos.y - m_scrolling.y };
	windowEvent.DragDelta = Point{ dragDelta.x, dragDelta.y };

	m_resizingDraggingInfoSignal(true, false);

	windowEvent.resizeDirection = *mouseAtResizerOpt;
	m_resizePositionableSignal(windowEvent);
}

void WDraftEditorImGui::HandleMouseRightButton()
{
	if (!ImGui::IsMouseDragging(ImGuiMouseButton_Right))
	{
		return;
	}

	ImGuiIO& io = ImGui::GetIO();
	m_scrolling.x += io.MouseDelta.x;
	m_scrolling.y += io.MouseDelta.y;
}

void WDraftEditorImGui::HandleMouseUp()
{
	if (!ImGui::IsMouseReleased(ImGuiMouseButton_Left))
	{
		return;
	}
	auto pos = ImGui::GetMousePos();

	auto windowEvent = event::WindowEvent();
	windowEvent.EventType = event::WindowEventType::MouseUp;
	windowEvent.MouseAt = Point{ pos.x - m_scrolling.x, pos.y - m_scrolling.y };

	EmitWindowEvent(windowEvent);
	m_resizingDraggingInfoSignal(false, false);
}

// ######################################### Mouse Handling ###########################################

// ########################################### Handlers ###############################################

void WDraftEditorImGui::HandleInput()
{
	ImVec2 canvasSize{ float(m_canvas->GetSize().x), float(m_canvas->GetSize().y) };
	ImVec2 canvasLeftTopPoint{ float(m_canvas->GetLeftTop().x), float(m_canvas->GetLeftTop().y) };

	ImGui::InvisibleButton("canvas", canvasSize, ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);
	const bool is_active = ImGui::IsItemActive();

	if (ImGui::IsMousePosValid())
	{
		HandleMouseLeftButtonDraggingOverResizers();

		if (is_active)
		{ // in work area
			HandleMouseInput();
		}

		// mouseUp triggers only outside of invisible button
		HandleMouseUp();
	}

	HandleMouseCursorStyle();
}

void WDraftEditorImGui::OnPresenterModelChange(const DomainPositionableModelEvent& evt)
{
	m_modelSnapshot = evt.PositionablesGroup;
}

// ########################################### Handlers ###############################################

} // namespace app::window
