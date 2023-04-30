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

	// <<interface>> IPositionable
	bool IsPositionableContainsPoint(const PointD& point) const noexcept override
	{
		return this->GetFrame().ContainsPoint(point);
	}

	const PointD& GetBasePoint() const noexcept final
	{
		return m_frame.pLeftTop;
	}

	FrameD GetFrame() const noexcept override
	{
		return m_frame;
	}

	using OnChangePositionableGroupArg = typename IBase::OnChangePositionableGroupArg;
	using OnChangePositionableArg = typename IBase::OnChangePositionableArg;
	void SetFrame(const FrameD& frame) override
	{
		m_frame = frame;
		m_changeSignal(OnChangePositionableGroupArg{}, OnChangePositionableArg{ this });
	}

	using Connection = typename IBase::Connection;
	using OnChange = typename IBase::OnChange;
	Connection DoOnChange(const OnChange& handler) override
	{
		return m_changeSignal.connect(handler);
	}

	IPositionableGroupSharedPtr GetPositionableGroup() override
	{
		return nullptr;
	}

	IPositionableGroupSharedConstPtr GetPositionableGroup() const override
	{
		return nullptr;
	}

	using Canvas = typename IBase::Canvas;
	void AddToCanvas(Canvas canvas) const override
	{
		if (canvas == nullptr)
		{
			throw std::runtime_error("[illusio][PositionableImpl] Can't draw positionable at canvas. Null given");
		}
	}
	// >>>>>>>>>>>>>>>>>>>>>>>>>>>

protected:
	using SizeD = common::axes::SizeD;

	constexpr PositionableImpl() = default;
	constexpr PositionableImpl(const PointD& basePoint, const SizeD& size)
		: m_frame(basePoint, size)
	{
	}

	void EmitChangeSignal(OnChangePositionableGroupArg positionables, OnChangePositionableArg positionable)
	{
		m_changeSignal(positionables, positionable);
	}

private:
	using SignalOnChange = illusio::common::signal<void(OnChangePositionableGroupArg, OnChangePositionableArg)>;

	FrameD m_frame = FrameD{};
	SignalOnChange m_changeSignal;
};

} // namespace illusio::domain
