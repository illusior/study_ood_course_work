#pragma once

#include "IPositionable_fwd.h"

#include "../IObject.h"

#include "domain/common/frame/CFrame/FrameD.h"
#include "domain/common/point/CPoint/PointD.h"

namespace illusio::domain
{

class IPositionable : public IObject
{
public:
	using PointD = common::axes::PointD;
	using FrameD = common::axes::FrameD;

	// BasePoint is leftTop point of FrameD
	virtual const PointD& GetBasePoint() const noexcept = 0;
	virtual FrameD GetFrame() const noexcept = 0;

	virtual void SetFrame(const FrameD& frame) = 0;

	virtual ~IPositionable() = default;
};

} // namespace illusio::domain
