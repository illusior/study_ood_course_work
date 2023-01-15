#pragma once

#include <memory>

namespace illusio::domain::shape
{

class IShapes;

using IShapesRawPtr = IShapes*;
using IShapesPtr = std::unique_ptr<IShapes>;
using IShapesSharedPtr = std::shared_ptr<IShapes>;

} // namespace illusio::domain::shape
