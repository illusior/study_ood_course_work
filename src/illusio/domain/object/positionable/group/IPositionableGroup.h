#pragma once

#include <optional>

#include "IPositionableGroup_fwd.h"

#include "../IPositionable.h"
#include "../IPositionables.h"

namespace illusio::domain
{

class IPositionableGroup : public IPositionable
	, public IPositionables
{
public:
	virtual ~IPositionableGroup() = default;
};

} // namespace illusio::domain
