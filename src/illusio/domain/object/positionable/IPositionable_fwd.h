#pragma once

#include <memory>

namespace illusio::domain
{

class IPositionable;

using IPositionableRawPtr = IPositionable*;
using IPositionablePtr = std::unique_ptr<IPositionable>;
using IPositionableSharedPtr = std::shared_ptr<IPositionable>;

} // namespace illusio::domain
