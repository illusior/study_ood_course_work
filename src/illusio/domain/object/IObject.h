#pragma once

#include "IObject_fwd.h"

#include "common/uuid/Uuid.h"

namespace illusio::domain
{

class IObject
{
public:
	using Uuid = illusio::common::Uuid::uuid;

	virtual Uuid GetUuid() const noexcept = 0;

	virtual ~IObject() = default;
};

} // namespace illusio::domain
