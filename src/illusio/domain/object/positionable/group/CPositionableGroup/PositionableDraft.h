#pragma once

#include <functional>

#include "PositionableGroup.hpp"

namespace illusio::domain
{

class PositionablesDraft : public PositionableGroup<IPositionableGroup>
{
public:
	using MyBase = PositionableGroup<IPositionableGroup>;

	using Connection = MyBase::Connection;

private:
	PositionablesDraft() = default;
};

} // namespace illusio::domain
