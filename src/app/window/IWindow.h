#pragma once

#include <string_view>

#include "IWindow_fwd.h"

namespace app::window
{

class IWindow
{
public:
	using Title = std::string_view;

	virtual bool Close() noexcept = 0;

	virtual void Update() = 0;

	virtual Title GetTitle() const noexcept = 0;

	virtual bool IsOpen() const noexcept = 0;

	virtual ~IWindow() = default;
};

} // namespace app::window
