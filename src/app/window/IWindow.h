#pragma once

#include <functional>
#include <string_view>

#include <illusio/common/signals/signal.hpp>

#include "event/WindowEvent.h"

#include "IWindow_fwd.h"

namespace app::window
{

class IWindow
{
public:
	using Title = std::string_view;

	virtual bool Init() = 0;
	virtual void Update() = 0;
	virtual bool Close() noexcept = 0;

	virtual Title GetTitle() const noexcept = 0;
	virtual bool IsOpen() const noexcept = 0;

	using Connection = illusio::common::connection;
	using OnWindowEventCallback = std::function<void(const event::WindowEvent&)>;
	virtual Connection DoOnFiringWindowEvent(const OnWindowEventCallback& handler) = 0;

	virtual ~IWindow() = default;
};

} // namespace app::window
