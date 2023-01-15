#pragma once

#include "ITriangle_fwd.h"

#include "../../IShapeSolid.h"

namespace illusio::domain::shape::solid
{

class ITriangle : public IShapeSolid
{
public:
	virtual PointD GetVertex1() const noexcept = 0;
	virtual PointD GetVertex2() const noexcept = 0;
	virtual PointD GetVertex3() const noexcept = 0;

	virtual ~ITriangle() = default;
};

} // namespace illusio::domain::shape::solid
