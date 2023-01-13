#pragma once

#include <memory>

namespace illusio::domain::drawable::shape
{

class IShape;

using IShapeRawPtr = IShape*;
using IShapePtr = std::unique_ptr<IShape>;

using IShapeSharedPtr = std::shared_ptr<IShape>;
using IShapeSharedConstPtr = std::shared_ptr<const IShape>;

} // namespace illusio::domain::drawable::shape
