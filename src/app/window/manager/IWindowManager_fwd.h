#pragma once

#include <memory>

namespace app::window
{

class IWindowManager;

using IWindowManagerRawPtr = IWindowManager*;
using IWindowManagerPtr = std::unique_ptr<IWindowManager>;
using IWindowManagerSharedPtr = std::shared_ptr<IWindowManager>;

} // namespace app::window
