#pragma once

#include "PositionableGroup.hpp"

namespace illusio::domain
{

class PositionablesDraft : public PositionableGroup<IPositionableGroup>
{
public:
	using MyBase = PositionableGroup<IPositionableGroup>;

	PositionablesDraft() = default;
};

} // namespace illusio::domain
