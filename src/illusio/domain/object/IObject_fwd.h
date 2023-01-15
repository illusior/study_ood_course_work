#pragma once

#include <memory>

namespace illusio::domain
{

class IObject;

using IObjectRawPtr = IObject*;
using IObjectPtr = std::unique_ptr<IObject>;
using IObjectSharedPtr = std::shared_ptr<IObject>;

} // namespace illusio::domain
