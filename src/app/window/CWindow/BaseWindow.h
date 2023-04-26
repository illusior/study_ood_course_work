#pragma once

#include "../IWindow.h"

namespace app::window
{

class BaseWindow : public IWindow
{
protected:
	explicit BaseWindow() = default;
	explicit BaseWindow(Title title);

	// <<interface>> IWindow
	bool Init() override;
	void Update() override;
	bool Close() noexcept override;

	Title GetTitle() const noexcept final;
	bool IsOpen() const noexcept final;
	// >>>>>>>>>>>>>>>>>>>>>

	virtual bool Begin() = 0;
	virtual void End() = 0;

	virtual bool Initialize();

	Title m_title = "Default Title";

private:
	bool m_isOpen = true;
	bool m_isInited = false;
};

} // namespace app::window
