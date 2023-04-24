#pragma once

#include <functional>
#include <optional>

#include "IPositionableDraft_fwd.h"

#include "../object/positionable/IPositionable.h"
#include "common/signals/signal.hpp"

namespace illusio::domain
{

class IPositionableDraft
{
public:
	using IPositionable = IPositionable;
	using Positionable = IPositionableSharedPtr;

	virtual void Insert(const Positionable& positionable, std::optional<size_t> index = std::nullopt) = 0;
	virtual void Remove(std::optional<size_t> index = std::nullopt) = 0;

	virtual Positionable GetPositionable(size_t index) = 0;
	virtual size_t GetPositionableCount() const noexcept = 0;

	using Connection = illusio::common::connection;
	using OnPositionableInsert = std::function<void(size_t)>;
	virtual Connection DoOnPositionableInsert(const OnPositionableInsert& handler) = 0;

	using OnPositionableRemove = std::function<void(size_t, IPositionable&)>;
	virtual Connection DonOnPositionableRemove(const OnPositionableRemove& handler) = 0;

	virtual ~IPositionableDraft() = default;
};

} // namespace illusio::domain
