#pragma once

#include <optional>

#include "IShapes_fwd.h"

#include "IShape.h"

namespace illusio::domain::drawable::shape
{

class IShapes
{
public:
	virtual size_t GetShapesCount() const noexcept = 0;
	virtual IShapeSharedPtr GetShape(size_t index) = 0;
	virtual IShapeSharedConstPtr GetShape(size_t index) const = 0;


	virtual void InsertShape(const IShapeSharedPtr& shape, std::optional<size_t> index = std::nullopt) = 0;
	virtual void RemoveShape(size_t index) = 0;

	virtual ~IShapes() = default;
};

} // namespace illusio::domain::drawable::shape
