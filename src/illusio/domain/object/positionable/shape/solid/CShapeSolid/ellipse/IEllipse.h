#pragma once

#include "IEllipse_fwd.h"

#include "../../IShapeSolid.h"

namespace illusio::domain::shape::solid
{

class IEllipse : public IShapeSolid
{
public:
	virtual ~IEllipse() = default;
};

} // namespace illusio::domain::shape::solid
