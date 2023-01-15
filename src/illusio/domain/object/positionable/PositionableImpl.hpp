#pragma once

#include "IPositionable.h"

#include "../../common/size/CSize/SizeD.h"
#include "../ObjectImpl.hpp"

namespace illusio::domain
{

template <typename Base = IPositionable>
class PositionableImpl : public ObjectImpl<Base>
{
public:
	using MyBase = ObjectImpl<Base>;

	using FrameD = typename Base::FrameD;
	using PointD = typename Base::PointD;

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
	}

protected:
	using SizeD = common::axes::SizeD;

	constexpr PositionableImpl() = default;
	
	constexpr PositionableImpl(const PointD& basePoint, const SizeD& size)
		: m_frame(basePoint, size)
	{
	}

private:
	FrameD m_frame;
};

} // namespace illusio::domain
