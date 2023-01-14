#pragma once

#include <memory>

#include "../IShape.h"

namespace illusio::domain::shape::solid
{

class IShapeSolid;

using IShapeSolidRawPtr = IShapeSolid*;
using IShapeSolidPtr = std::unique_ptr<IShapeSolid>;
using IShapeSolidSharedPtr = std::shared_ptr<IShapeSolid>;

} // namespace illusio::domain::shape::solid
