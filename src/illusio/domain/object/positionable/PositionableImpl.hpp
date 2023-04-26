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
	using UuidOpt = typename IBase::UuidOpt;
	UuidOpt GetUuidOfPositionableAtPoint(const PointD& point)
	{
		if (auto frame = this->GetFrame();
			frame.ContainsPoint(point))
		{
			return this->GetUuid();
		}

		return std::nullopt;
	}

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
		m_changeSignal();
	}

	using Connection = typename IBase::Connection;
	using OnFrameChange = typename IBase::OnFrameChange;
	Connection DoOnFrameChange(const OnFrameChange& handler) override
	{
		return m_frameChanged.connect(handler);
	}

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
	void DrawAtCanvas(Canvas canvas) const override
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

	virtual void EmitChangeSignal()
	{
		m_changeSignal();
	}

private:
	using Signal = illusio::common::signal<void(const FrameD&)>;
	using SignalOnChange = illusio::common::signal<void()>;

	FrameD m_frame = FrameD{};

	Signal m_frameChanged;
	SignalOnChange m_changeSignal;
};

} // namespace illusio::domain
