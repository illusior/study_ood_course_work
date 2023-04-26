#pragma once

#include "IWindowManager_fwd.h"

#include "../IWindow.h"

namespace app::window
{

class IWindowManager
{
public:
	virtual void Update() = 0;
	virtual void Render() = 0;

	using Window = IWindowPtr;
	virtual void AddWindow(Window&& window) = 0;

	virtual ~IWindowManager() = default;
};

} // namespace app::window
