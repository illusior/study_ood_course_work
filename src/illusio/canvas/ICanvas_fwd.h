#pragma once

#include <memory>

namespace illusio::canvas
{

class ICanvas;

using ICanvasRawPtr = ICanvas*;
using ICanvasPtr = std::unique_ptr<ICanvas>;
using ICanvasSharedPtr = std::shared_ptr<ICanvas>;

} // namespace illusio::canvas
