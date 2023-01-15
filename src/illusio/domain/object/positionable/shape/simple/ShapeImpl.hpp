#pragma once

#include "../IShape.h"

#include "../../PositionableImpl.hpp"

namespace illusio::domain::shape::simple
{

template <typename IBase = IShape>
class ShapeImpl : public PositionableImpl<IBase>
{
public:
	using MyBase = PositionableImpl<IBase>;

	using Style = typename IBase::Style;
	using StylePtr = typename IBase::StylePtr;

	// <<interface>> IShape
	const Style& GetOutlineStyle() const noexcept override
	{
		return *m_outlineStyle;
	}

	IShapeGroupSharedPtr GetShapeGroup() override
	{
		return nullptr;
	}

	IShapeGroupSharedConstPtr GetShapeGroup() const override
	{
		return nullptr;
	}

	using Connection = typename IBase::Connection;
	using OnFrameChange = typename IBase::OnFrameChange;
	Connection DoOnFrameChange(const OnFrameChange& handler) override
	{
		return m_frameChanged.connect(handler);
	}
	// >>>>>>>>>>>>>>>>>>>>

protected:
	using PointD = typename IBase::PointD;

	using SizeD = MyBase::SizeD;

	explicit constexpr ShapeImpl()
		: m_frameChanged()
		, m_outlineStyle(std::make_unique<common::Style>())
	{
	}

	explicit constexpr ShapeImpl(const PointD& basePoint, const SizeD& size, StylePtr&& outlineStyle)
		: MyBase(basePoint, size)
		, m_frameChanged()
		, m_outlineStyle(std::move(outlineStyle))
	{
	}

private:
	using FrameD = typename IBase::FrameD;
	using Signal = illusio::common::signal<void(const FrameD&)>;

	Signal m_frameChanged;
	StylePtr m_outlineStyle;
};

} // namespace illusio::domain::shape::simple
