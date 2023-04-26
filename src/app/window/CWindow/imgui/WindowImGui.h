#pragma once

#include "../BaseWindow.h"

namespace app::window
{

class WindowImGui : public BaseWindow
{
public:
	using MyBase = BaseWindow;

protected:
	explicit WindowImGui() = default;
	explicit WindowImGui(Title title);

	// <<interface>> IWindow
	void Update() final;
	// >>>>>>>>>>>>>>>>>>>>>

	// <<abstract>> BaseWindow
	bool Begin() override;
	void End() override;
	// >>>>>>>>>>>>>>>>>>>>>>

	virtual void RenderContent() = 0;

	bool m_hasCloseButton = false;
};

} // namespace app::window
