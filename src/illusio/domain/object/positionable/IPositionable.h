#pragma once

#include "IPositionable_fwd.h"

#include "../IObject.h"

#include "common/signals/signal.hpp"
#include "domain/common/frame/CFrame/FrameD.h"
#include "domain/common/point/CPoint/PointD.h"

#include "group/IPositionableGroup_fwd.h"

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

	using Connection = illusio::common::connection;
	using OnFrameChange = std::function<void(const FrameD&)>;
	virtual Connection DoOnFrameChange(const OnFrameChange& handler) = 0;

	virtual IPositionableGroupSharedPtr GetPositionableGroup() = 0;
	virtual IPositionableGroupSharedConstPtr GetPositionableGroup() const = 0;

	virtual ~IPositionable() = default;
};

} // namespace illusio::domain
