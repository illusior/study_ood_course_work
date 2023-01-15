#pragma once

#include "IObject.h"

namespace illusio::domain
{

template <typename Base = IObject>
class ObjectImpl : public Base
{
public:
	using Uuid = typename Base::Uuid;

	constexpr Uuid GetUuid() const noexcept final
	{
		return m_uuid;
	}

protected:
	constexpr ObjectImpl()
		: m_uuid(std::move(illusio::common::Uuid::CreateUuid()))
	{
	}

private:
	Uuid m_uuid;
};

} // namespace illusio::app
