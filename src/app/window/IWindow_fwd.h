#pragma once

#include <memory>

namespace app::window
{

class IWindow;

using IWindowRawPtr = IWindow*;
using IWindowPtr = std::unique_ptr<IWindow>;
using IWindowSharedPtr = std::shared_ptr<IWindow>;

} // namespace app::window
