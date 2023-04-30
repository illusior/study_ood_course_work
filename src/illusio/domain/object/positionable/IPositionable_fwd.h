#pragma once

#include <memory>

namespace illusio::domain
{

class IPositionable;

using IPositionableRawPtr = IPositionable*;
using IPositionableRawConstPtr = const IPositionable*;

using IPositionablePtr = std::unique_ptr<IPositionable>;
using IPositionableSharedPtr = std::shared_ptr<IPositionable>;
using IPositionableSharedConstPtr = std::shared_ptr<const IPositionable>;

} // namespace illusio::domain
