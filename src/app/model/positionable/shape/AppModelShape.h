#pragma once

#include "illusio/domain/object/positionable/shape/IShape.h"

namespace app::model
{

class AppModelShape
{
public:
	using IShape = illusio::domain::shape::IShape;
	using Shape = illusio::domain::shape::IShapeSharedPtr;

	using Connection = IShape::Connection;
	using FrameD = IShape::FrameD;
	using OnFrameChange = IShape::OnFrameChange;

	AppModelShape(const Shape& shape);

	FrameD GetFrame() const noexcept;
	void SetFrame(const FrameD& frame); 

	Connection DoOnFrameChange(const OnFrameChange& handler);

private:
	Shape m_shape;
};

} // namespace app::model
