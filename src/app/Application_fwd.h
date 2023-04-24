#pragma once

#include <memory>

namespace app
{

class Application;

using ApplicationRawPtr = Application*;
using ApplicationPtr = std::unique_ptr<Application>;
using ApplicationSharedPtr = std::shared_ptr<Application>;

} // namespace app
