#pragma once

#include <functional>

#include "../IPositionable.h"
#include "IShape_fwd.h"

#include "domain/common/domain_common.h"

namespace illusio::domain::shape
{

class IShape : public IPositionable
{
public:
	using Style = common::IStyle;
	using StylePtr = common::IStylePtr;

	virtual const Style& GetOutlineStyle() const noexcept = 0;

	virtual ~IShape() = default;
};

} // namespace illusio::domain::shape
