#pragma once

#include <memory>

namespace illusio::domain
{

class IPositionableGroup;

using IPositionableGroupRawPtr = IPositionableGroup*;
using IPositionableGroupRawConstPtr = const IPositionableGroup*;

using IPositionableGroupPtr = std::unique_ptr<IPositionableGroup>;

using IPositionableGroupSharedPtr = std::shared_ptr<IPositionableGroup>;
using IPositionableGroupSharedConstPtr = std::shared_ptr<const IPositionableGroup>;

} // namespace illusio::domain
