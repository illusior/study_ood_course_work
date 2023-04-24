#pragma once

#include "IPositionable.h"

#include "../../common/size/CSize/SizeD.h"
#include "../ObjectImpl.hpp"

namespace illusio::domain
{

template <typename IBase = IPositionable>
class PositionableImpl : public ObjectImpl<IBase>
{
public:
	using MyBase = ObjectImpl<IBase>;

	using FrameD = typename IBase::FrameD;
	using PointD = typename IBase::PointD;

	const PointD& GetBasePoint() const noexcept final
	{
		return m_frame.pLeftTop;
	}

	FrameD GetFrame() const noexcept override
	{
		return m_frame;
	}

	void SetFrame(const FrameD& frame) override
	{
		m_frame = frame;
		m_frameChanged(m_frame);
	}

	using Connection = typename IBase::Connection;
	using OnFrameChange = typename IBase::OnFrameChange;
	Connection DoOnFrameChange(const OnFrameChange& handler) override
	{
		return m_frameChanged.connect(handler);
	}

	IPositionableGroupSharedPtr GetPositionableGroup() override
	{
		return nullptr;
	}

	IPositionableGroupSharedConstPtr GetPositionableGroup() const override
	{
		return nullptr;
	}

protected:
	using SizeD = common::axes::SizeD;

	constexpr PositionableImpl() = default;
	constexpr PositionableImpl(const PointD& basePoint, const SizeD& size)
		: m_frame(basePoint, size)
	{
	}

private:
	using Signal = illusio::common::signal<void(const FrameD&)>;

	FrameD m_frame = FrameD{};
	Signal m_frameChanged;
};

} // namespace illusio::domain
