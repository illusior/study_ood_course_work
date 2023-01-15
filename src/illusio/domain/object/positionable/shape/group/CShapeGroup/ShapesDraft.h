﻿#pragma once

#include <functional>

#include "ShapeGroup.hpp"

namespace illusio::domain::shape
{

class ShapesDraft : public ShapeGroup<IShapeGroup>
{
public:
	using MyBase = ShapeGroup<illusio::domain::shape::IShapeGroup>;

	using Connection = MyBase::Connection;

	// <<interface>> IShapes
	void InsertShape(const IShapeSharedPtr& shape, std::optional<size_t> index = std::nullopt) override;
	void RemoveShape(size_t index) override;
	// >>>>>>>>>>>>>>>>>>>>>

	using OnShapeAdded = std::function<void(size_t)>;
	Connection DoOnShapeAdded(const OnShapeAdded& handler);

	using OnShapeDeleted = std::function<void(size_t, IShape&)>;
	Connection DoOnShapeDeleted(const OnShapeDeleted& handler);

private:
	using SignalShapeAdded = illusio::common::signal<void(size_t)>;
	using SignalShapeDeleted = illusio::common::signal<void(size_t, IShape&)>;

	SignalShapeAdded m_shapeAdded;
	SignalShapeDeleted m_shapeDeleted;
};

} // namespace illusio::domain::shape