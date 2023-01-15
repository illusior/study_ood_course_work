#pragma once

#include <memory>

namespace illusio::domain::shape::solid
{

class IRectangle;

using IRectangleRawPtr = IRectangle*;
using IRectanglePtr = std::unique_ptr<IRectangle>;
using IRectangleSharedPtr = std::shared_ptr<IRectangle>;

} // namespace illusio::domain::shape::solid
