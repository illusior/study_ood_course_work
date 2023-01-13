#pragma once

#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_generators.hpp"

namespace illusio::common
{

using Uuid = boost::uuids::uuid;
using UuidGeneratorMT19937 = boost::uuids::random_generator_mt19937;

} // namespace illusio::common
