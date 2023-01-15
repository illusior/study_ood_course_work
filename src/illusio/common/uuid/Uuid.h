#pragma once

#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_generators.hpp"

namespace illusio::common
{

class Uuid final
{
public:
	using uuid = boost::uuids::uuid;
	using UuidGenerator = boost::uuids::random_generator_mt19937;

	Uuid() = delete;
	Uuid(const Uuid&) = delete;

	static uuid CreateUuid() noexcept;

	void operator=(const Uuid&) = delete;
};

} // namespace illusio::common
