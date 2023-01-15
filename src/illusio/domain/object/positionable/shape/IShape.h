#pragma once

#include <functional>

#include "../IPositionable.h"
#include "IShape_fwd.h"

#include "common/signals/signal.hpp"
#include "domain/common/domain_common.h"
#include "group/IShapeGroup_fwd.h"

namespace illusio::domain::shape
{

class IShape : public IPositionable
{
public:
	using Style = common::IStyle;
	using StylePtr = common::IStylePtr;

	virtual const Style& GetOutlineStyle() const noexcept = 0;

	virtual IShapeGroupSharedPtr GetShapeGroup() = 0;
	virtual IShapeGroupSharedConstPtr GetShapeGroup() const = 0;

	using Connection = illusio::common::connection;
	using OnFrameChange = std::function<void(const FrameD&)>;
	virtual Connection DoOnFrameChange(const OnFrameChange& handler) = 0;

	virtual ~IShape() = default;
};

} // namespace illusio::domain::shape
