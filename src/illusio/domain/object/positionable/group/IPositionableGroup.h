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

	using FrameOpt = std::optional<FrameD>;
	using UuidOpt = std::optional<Uuid>;
	virtual void SelectPositionable(const UuidOpt& uuid) = 0;
	virtual const FrameOpt& GetSelectionFrame() const noexcept = 0;

private:
	// TODO: implement in base PositionableGroup, but for now make it unaccessable
	using IPositionable::DoOnFrameChange;
	using IPositionable::SetFrame;
};

} // namespace illusio::domain
