#pragma once

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

private:
	// TODO: implement in base PositionableGroup, but for now make it unaccessable
	using IPositionable::DoOnFrameChange;
	using IPositionable::SetFrame;
};

} // namespace illusio::domain
