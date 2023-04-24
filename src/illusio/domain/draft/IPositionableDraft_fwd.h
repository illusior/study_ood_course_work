#pragma once

#include <memory>

namespace illusio::domain
{

class IPositionableDraft;

using IPositionableDraftRawPtr = IPositionableDraft*;
using IPositionableDraftPtr = std::unique_ptr<IPositionableDraft>;
using IPositionableDraftSharedPtr = std::shared_ptr<IPositionableDraft>;

} // namespace illusio::domain
