#pragma once

namespace illusio::domain::event
{

enum class DomainPositionableModelEventTypes
{
	FrameChanged = 0,
	InsertPositionable,
	Rearranged,
	RemovePositionable,
};

} // namespace illusio::domain::event
