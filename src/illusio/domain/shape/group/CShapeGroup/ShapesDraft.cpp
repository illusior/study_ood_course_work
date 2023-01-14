#include "pch_illusio.h"

#include "ShapesDraft.h"

namespace illusio::domain::shape
{

using Connection = ShapesDraft::Connection;

void ShapesDraft::InsertShape(const IShapeSharedPtr& shape, std::optional<size_t> index)
{
	MyBase::InsertShape(shape, index);

	m_shapeAdded(index.has_value() ? *index : GetShapesCount() - 1);
}

void ShapesDraft::RemoveShape(size_t index)
{
	auto removingShape = GetShape(index);

	MyBase::RemoveShape(index);

	m_shapeDeleted(index, *removingShape);
}

Connection ShapesDraft::DoOnShapeAdded(const OnShapeAdded& handler)
{
	return m_shapeAdded.connect(handler);
}

Connection ShapesDraft::DoOnShapeDeleted(const OnShapeDeleted& handler)
{
	return m_shapeDeleted.connect(handler);
}

} // namespace illusio::domain::shape
