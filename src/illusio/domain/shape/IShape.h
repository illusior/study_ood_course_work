#pragma once

#include <functional>

#include "IShape_fwd.h"

#include "group/IShapeGroup_fwd.h"

#include "common/signals/signal.hpp"
#include "common/uuid/uuid.hpp"
#include "domain/common/domain_common.h"

namespace illusio::domain::shape
{

class IShape
{
public:
	using FrameD = common::FrameD;
	using PointD = common::PointD;
	using Style = common::IStyle;
	using StylePtr = common::IStylePtr;
	using Uuid = illusio::common::Uuid;

	virtual const PointD& GetBasePoint() const noexcept = 0;
	virtual const Style& GetOutlineStyle() const noexcept = 0;
	virtual const Uuid& GetUuid() const noexcept = 0;
	virtual FrameD GetFrame() const noexcept = 0;

	virtual void SetFrame(const FrameD& frame) = 0;

	virtual IShapeGroupSharedPtr GetShapeGroup() = 0;
	virtual IShapeGroupSharedConstPtr GetShapeGroup() const = 0;

	using Connection = illusio::common::connection;
	using OnFrameChange = std::function<void(const FrameD&)>;
	virtual Connection DoOnFrameChange(const OnFrameChange& handler) = 0;

	virtual ~IShape() = default;
};

} // namespace illusio::domain::shape
