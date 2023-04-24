#pragma once

#include <memory>

namespace illusio::domain
{

class IPositionables;

using IPositionablesRawPtr = IPositionables*;
using IPositionablesPtr = std::unique_ptr<IPositionables>;
using IPositionablesSharedPtr = std::shared_ptr<IPositionables>;

} // namespace illusio::domain
