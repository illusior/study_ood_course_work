#include "pch_illusio.h"

#include "ShapesDraft.h"

namespace illusio::domain::drawable::shape
{

using Connection = ShapesDraft::Connection;

Connection ShapesDraft::DoOnShapeAdded(const OnShapeAdded& handler)
{
	return m_shapeAdded.connect(handler);
}

Connection ShapesDraft::DoOnShapeDeleted(const OnShapeDeleted& handler)
{
	return m_shapeDeleted.connect(handler);
}

} // namespace illusio::domain::drawable::shape
