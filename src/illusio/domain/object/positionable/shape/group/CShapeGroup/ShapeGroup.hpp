#pragma once

#include <list>

#include "../IShapeGroup.h"
#include "../../simple/ShapeImpl.hpp"

#include "domain/common/style/CStyle/StyleComposite.h"

namespace illusio::domain::shape
{

template <typename IBase = IShapeGroup>
class ShapeGroup : public simple::ShapeImpl<IBase>
	, public std::enable_shared_from_this<ShapeGroup<IBase>>
{
	// clang-format off
	// search for passKey idiom: when ctor is hidden for std::make_shared
	struct pass_key { explicit constexpr pass_key(){} };
	// clang-format on

public:
	using IShape = shape::IShape;

	using FrameD = typename IBase::FrameD;
	using Style = typename IBase::Style;

	static IShapeGroupSharedPtr Create()
	{
		return std::make_shared<ShapeGroup>(pass_key{});
	}

	explicit constexpr ShapeGroup(pass_key)
		: m_shapes()
		, m_outlineStyle()
	{
	}

	// <<interface>> IShape
	const Style& GetOutlineStyle() const noexcept final
	{
		return *m_outlineStyle;
	}

	FrameD GetFrame() const noexcept final
	{
		std::vector<FrameD> rects;
		rects.reserve(GetShapesCount());
		for (const auto& shape : m_shapes)
		{
			rects.push_back(shape->GetFrame());
		}

		return domain::common::axes::GetMaxFrame<double>(rects);
	}

	void SetFrame(const FrameD& frame) final
	{
	}

	IShapeGroupSharedPtr GetShapeGroup() final
	{
		return this->shared_from_this();
	}

	IShapeGroupSharedConstPtr GetShapeGroup() const final
	{
		return this->shared_from_this();
	}
	// >>>>>>>>>>>>>>>>>>>>

	// <<interface>> IShapes
	size_t GetShapesCount() const noexcept final
	{
		return m_shapes.size();
	}

	IShapeSharedPtr GetShape(size_t index) final
	{
		if (index >= m_shapes.size())
		{
			throw std::out_of_range("Failed to get shape at" + std::to_string(index) + " index. Index is out of range");
		}

		auto it = m_shapes.begin();
		std::advance(it, index);

		return *it;
	}

	IShapeSharedConstPtr GetShape(size_t index) const final
	{
		if (index >= m_shapes.size())
		{
			throw std::out_of_range("Failed to get shape at " + std::to_string(index) + " index. Index is out of range");
		}

		auto it = m_shapes.begin();
		std::advance(it, index);

		return *it;
	}

	void InsertShape(const IShapeSharedPtr& shape, std::optional<size_t> index = std::nullopt) override
	{
		if (std::addressof(*shape) == this)
		{
			return;
		}

		const auto insertIndex = (index.has_value())
			? std::min(*index, m_shapes.size())
			: m_shapes.size();

		auto it = m_shapes.begin();
		std::advance(it, insertIndex);

		m_shapes.insert(it, shape);
	}

	void RemoveShape(size_t index) override
	{
		if (index >= m_shapes.size())
		{
			throw std::out_of_range("Failed to remove shape at " + std::to_string(index) + " index. Index is out of range");
		}

		auto it = m_shapes.begin();
		std::advance(it, index);

		m_shapes.erase(it);
	}
	// >>>>>>>>>>>>>>>>>>>>>

protected:
	using Connection = typename IBase::Connection;

	explicit constexpr ShapeGroup()
		: m_shapes()
		, m_outlineStyle()
	{
	}

private:
	using OnFrameChange = typename IBase::OnFrameChange;
	using StyleComposite = typename IBase::StylePtr;

	using ShapesContainer = std::list<IShapeSharedPtr>;

	// TODO: see IShapeGroup.h
	Connection DoOnFrameChange(const OnFrameChange&) final
	{
		return Connection();
	}

	ShapesContainer m_shapes;
	// TODO: compositeStyle for fillColor? ShapeGroup can hold IShape and ISolidShape
	StyleComposite m_outlineStyle;
};

} // namespace illusio::domain::shape
