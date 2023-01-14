#pragma once

#include "IRectangle_fwd.h"

#include "../../IShapeSolid.h"

namespace illusio::domain::shape::solid
{

class IRectangle : public IShapeSolid
{
public:
	virtual ~IRectangle() = default;
};

} // namespace illusio::domain::shape::solid
