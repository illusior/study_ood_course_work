#pragma once

#include <set>

#include <illusio/domain/common/point/CPoint/PointD.h>

#include "WindowEventTypes.h"

namespace app::window::event
{

struct WindowEvent
{
	using Point = illusio::domain::common::axes::PointD;
	Point MouseAt;

	Point DragDelta;

	WindowEventType EventType;

	using KeyboardInputs = std::set<Keyboard>;
	KeyboardInputs KeyBoardKeys;
};

} // namespace app::window::event
