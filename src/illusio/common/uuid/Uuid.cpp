﻿#include "pch_illusio.h"

#include "uuid.h"

namespace illusio::common
{

static Uuid::UuidGenerator UUID_GENERATOR = Uuid::UuidGenerator();

Uuid::uuid Uuid::CreateUuid() noexcept
{
	return UUID_GENERATOR();
}

} // namespace illusio::common
