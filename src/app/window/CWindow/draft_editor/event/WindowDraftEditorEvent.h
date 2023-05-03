#pragma once

#include "WindowDraftEditorEventTypes.h"

#include "app/window/event/WindowEvent.h"

namespace app::window::event
{

struct WindowDraftEditorEvent : WindowEvent
{
	ResizeDirection ResizeDirection;
};

} // namespace app::window::event
