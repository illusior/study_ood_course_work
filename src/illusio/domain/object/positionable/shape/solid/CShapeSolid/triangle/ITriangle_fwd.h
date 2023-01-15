#pragma once

#include <memory>

namespace illusio::domain::shape::solid
{

class ITriangle;

using ITriangleRawPtr = ITriangle*;
using ITrianglePtr = std::unique_ptr<ITriangle>;
using ITriangleSharedPtr = std::shared_ptr<ITriangle>;

} // namespace illusio::domain::shape::solid
