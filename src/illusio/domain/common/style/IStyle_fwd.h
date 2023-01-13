#pragma once

#include <memory>

namespace illusio::domain::common::style
{

class IStyle;

using IStyleRawPtr = IStyle*;
using IStylePtr = std::unique_ptr<IStyle>;
using IStyleSharedPtr = std::shared_ptr<IStyle>;

} // namespace illusio::domain::common::style
