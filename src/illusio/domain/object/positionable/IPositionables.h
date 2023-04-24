#pragma once

#include <optional>

#include "IPositionables_fwd.h"

#include "IPositionable.h"

namespace illusio::domain
{

class IPositionables
{
public:
	virtual size_t GetPositionablesCount() const noexcept = 0;
	virtual IPositionableSharedPtr GetPositionable(size_t index) = 0;
	virtual IPositionableSharedConstPtr GetPositionable(size_t index) const = 0;

	virtual void InsertPositionable(const IPositionableSharedPtr& Positionable, std::optional<size_t> index = std::nullopt) = 0;
	virtual void RemovePositionable(size_t index) = 0;

	virtual ~IPositionables() = default;
};

} // namespace illusio::domain
