#pragma once

#include <list>

#include "../IShapeGroup.h"

#include "common/uuid/uuid.hpp"
#include "domain/common/style/CStyle/StyleComposite.h"

namespace illusio::domain::drawable::shape
{

class ShapeGroup : public IShapeGroup
	, public std::enable_shared_from_this<ShapeGroup>
{
	// clang-format off
	// search for passKey idiom: when ctor is hidden for std::make_shared
	struct pass_key { explicit constexpr pass_key(){} };
	// clang-format on

public:
	static IShapeGroupSharedPtr Create();

	explicit ShapeGroup(pass_key);

	// <<interface>> IShape
	constexpr const PointD& GetBasePoint() const noexcept final;
	constexpr const Style& GetOutlineStyle() const noexcept final;
	constexpr const Uuid& GetUuid() const noexcept final;
	FrameD GetFrame() const noexcept final;

	constexpr void SetFrame(const FrameD& frame) final;

	IShapeGroupSharedPtr GetShapeGroup() final;
	IShapeGroupSharedConstPtr GetShapeGroup() const final;
	// >>>>>>>>>>>>>>>>>>>>

	// <<interface>> IShapes
	size_t GetShapesCount() const noexcept final;
	IShapeSharedPtr GetShape(size_t index) final;
	IShapeSharedConstPtr GetShape(size_t index) const final;

	void InsertShape(const IShapeSharedPtr& shape, std::optional<size_t> index = std::nullopt) final;
	void RemoveShape(size_t index) final;
	// >>>>>>>>>>>>>>>>>>>>>

protected:
	explicit ShapeGroup();

private:
	using StyleComposite = domain::common::IStylePtr;
	using ShapesContainer = std::list<IShapeSharedPtr>;
	using Uuid = illusio::common::Uuid;

	// TODO: see IShapeGroup.h
	Connection DoOnFrameChange(const OnFrameChange&) final;

	Uuid m_uuid; // TODO: leave here or make super class for all shapes
	ShapesContainer m_shapes;
	mutable PointD m_basePoint = PointD{}; // TODO: make frame and basePoint cachable
	// TODO: compositeStyle for fillColor? ShapeGroup can hold IShape and ISolidShape
	StyleComposite m_outlineStyle;
};

} // namespace illusio::domain::drawable::shape
