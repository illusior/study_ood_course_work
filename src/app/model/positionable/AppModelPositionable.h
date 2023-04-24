#pragma once

#include "illusio/domain/object/positionable/IPositionable.h"

namespace app::model
{

class AppModelPositionable
{
public:
	using IPositionable = illusio::domain::IPositionable;
	using Positionable = illusio::domain::IPositionableSharedPtr;

	using Connection = IPositionable::Connection;
	using FrameD = IPositionable::FrameD;
	using OnFrameChange = IPositionable::OnFrameChange;

	AppModelPositionable(const Positionable& shape);

	FrameD GetFrame() const noexcept;
	void SetFrame(const FrameD& frame); 

	Connection DoOnFrameChange(const OnFrameChange& handler);

private:
	Positionable m_positionable;
};

} // namespace app::model
