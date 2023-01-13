#pragma once

#include "IShapeGroup_fwd.h"

#include "../IShape.h"
#include "../IShapes.h"

namespace illusio::domain::drawable::shape
{

class IShapeGroup : public IShape
	, public IShapes
{
public:
	virtual ~IShapeGroup() = default;

private:
	// TODO: implement in base ShapeGroup, but for now make it unaccessable
	using IShape::DoOnFrameChange;
	using IShape::SetFrame;
};

} // namespace illusio::domain::drawable::shape
