#pragma once

#include <memory>

namespace illusio::domain::shape::solid
{

class IEllipse;

using IEllipseRawPtr = IEllipse*;
using IEllipsePtr = std::unique_ptr<IEllipse>;
using IEllipseSharedPtr = std::shared_ptr<IEllipse>;

} // namespace illusio::domain::shape::solid
