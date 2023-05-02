#pragma once

namespace app::window::event
{

enum class Keyboard
{
	LeftCtrl = 0,
	Delete,
};

enum class WindowEventType
{
	MouseDown = 0,
	MouseUp,
	MouseClick,
	MouseDrag,
};

} // namespace app::window::event
