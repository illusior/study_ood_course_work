#pragma once

#include "../IShape.h"

namespace illusio::domain::shape::simple
{

template <typename Base = IShape>
class ShapeImpl : public Base
{
public:
	using MyBase = Base;

	using FrameD = typename MyBase::FrameD;
	using PointD = typename MyBase::PointD;
	using Style = typename MyBase::Style;
	using StylePtr = typename MyBase::StylePtr;
	using Uuid = typename MyBase::Uuid;

	// <<interface>> IShape
	const PointD& GetBasePoint() const noexcept final
	{
		return m_frame.pLeftTop;
	}

	const Style& GetOutlineStyle() const noexcept final
	{
		return *m_outlineStyle;
	}

	const Uuid& GetUuid() const noexcept final
	{
		return m_uuid;
	}

	FrameD GetFrame() const noexcept override
	{
		return m_frame;
	}

	void SetFrame(const FrameD& frame) override
	{
		m_frame = frame;
	}

	IShapeGroupSharedPtr GetShapeGroup() override
	{
		return nullptr;
	}

	IShapeGroupSharedConstPtr GetShapeGroup() const override
	{
		return nullptr;
	}

	using Connection = typename MyBase::Connection;
	using OnFrameChange = typename MyBase::OnFrameChange;
	Connection DoOnFrameChange(const OnFrameChange& handler) override
	{
		return m_frameChanged.connect(handler);
	}
	// >>>>>>>>>>>>>>>>>>>>

protected:
	using UuidGenerator = illusio::common::UuidGeneratorMT19937;
	explicit constexpr ShapeImpl()
		: m_frame()
		, m_frameChanged()
		, m_outlineStyle(std::make_unique<common::Style>())
		, m_uuid(UuidGenerator{}())
	{
	}

	using SizeD = common::SizeD;
	explicit constexpr ShapeImpl(const PointD& basePoint, const SizeD& size, StylePtr&& outlineStyle)
		: m_frame(std::move(FrameD{ basePoint, size }))
		, m_frameChanged()
		, m_outlineStyle(std::move(outlineStyle))
		, m_uuid(UuidGenerator{}())
	{
	}

private:
	using Signal = illusio::common::signal<void(const FrameD&)>;

	FrameD m_frame;
	Signal m_frameChanged;
	StylePtr m_outlineStyle;
	Uuid m_uuid;
};

} // namespace illusio::domain::shape::simple
