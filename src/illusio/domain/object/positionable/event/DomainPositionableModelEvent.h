#pragma once

#include "../IPositionable.h"

#include "DomainPositionableModelEventTypes.h"

namespace illusio::domain::event
{

struct DomainPositionableModelEvent
{
	using ConstPositionables = IPositionableGroupRawConstPtr;
	using ConstPositionable = IPositionableRawConstPtr;
	using PositionableChangeInitiatorIndex = size_t;

	ConstPositionables PositionablesGroup;
	ConstPositionable PositionableEventInitiator;
	PositionableChangeInitiatorIndex PositionableChangedAtIndexInGroup;
	DomainPositionableModelEventTypes EventType;
};

} // namespace illusio::domain::event
