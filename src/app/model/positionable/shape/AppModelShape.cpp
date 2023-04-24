#include "pch.h"

#include "AppModelShape.h"

namespace app::model
{

AppModelShape::AppModelShape(const Shape& shape)
	: m_shape(shape)
{
}

AppModelShape::FrameD AppModelShape::GetFrame() const noexcept
{
	return m_shape->GetFrame();
}

void AppModelShape::SetFrame(const FrameD& frame)
{
	m_shape->SetFrame(frame);
}

AppModelShape::Connection AppModelShape::DoOnFrameChange(const OnFrameChange& handler)
{
	return m_shape->DoOnFrameChange(handler);
}

} // namespace app::model
