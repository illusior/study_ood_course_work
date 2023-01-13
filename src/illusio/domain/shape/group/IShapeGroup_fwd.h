#pragma once

#include <memory>

namespace illusio::domain::drawable::shape
{

class IShapeGroup;

using IShapeGroupRawPtr = IShapeGroup*;
using IShapeGroupPtr = std::unique_ptr<IShapeGroup>;

using IShapeGroupSharedPtr = std::shared_ptr<IShapeGroup>;
using IShapeGroupSharedConstPtr = std::shared_ptr<const IShapeGroup>;

} // namespace illusio::domain::drawable::shape
