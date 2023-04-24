#pragma once

#include "Application_fwd.h"

#include "window/manager/IWindowManager.h"

namespace app
{

class Application
{
public:
	~Application();

	static Application& GetInstance();

	void Start();

private:
	explicit Application();

	using WindowManager = window::IWindowManagerPtr;

	WindowManager m_windowManager;
};

} // namespace app
