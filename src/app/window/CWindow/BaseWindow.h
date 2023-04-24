#pragma once

#include "../IWindow.h"

namespace app::window
{

class BaseWindow : public IWindow
{
public:
	~BaseWindow();

protected:
	explicit constexpr BaseWindow() = default;
	explicit constexpr BaseWindow(Title title)
		: m_title(title)
		, m_isOpen(true)
	{
	}

	// <<interface>> IWindow
	bool Close() noexcept override;

	Title GetTitle() const noexcept final;

	bool IsOpen() const noexcept final;
	// >>>>>>>>>>>>>>>>>>>>>

	virtual bool Begin() = 0;
	virtual void End() = 0;

	Title m_title = "Default Title";

private:
	bool m_isOpen = true;
};

} // namespace app::window
