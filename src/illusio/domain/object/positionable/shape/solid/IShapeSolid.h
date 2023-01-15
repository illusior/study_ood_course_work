#pragma once

#include "IShapeSolid_fwd.h"

namespace illusio::domain::shape::solid
{

class IShapeSolid : public IShape
{
public:
	virtual const Style& GetFillColor() const noexcept = 0;

	virtual ~IShapeSolid() = default;
};

} // namespace illusio::domain::shape::solid
