#include "pch.h"

#include "AppModelPositionable.h"

namespace app::model
{

AppModelPositionable::AppModelPositionable(const Positionable& shape)
	: m_positionable(shape)
{
}

AppModelPositionable::FrameD AppModelPositionable::GetFrame() const noexcept
{
	return m_positionable->GetFrame();
}

void AppModelPositionable::SetFrame(const FrameD& frame)
{
	m_positionable->SetFrame(frame);
}

AppModelPositionable::Connection AppModelPositionable::DoOnFrameChange(const OnFrameChange& handler)
{
	return m_positionable->DoOnFrameChange(handler);
}

} // namespace app::model
