#pragma once

#include <vector>

#include "../IPositionableDraft.h"

namespace illusio::domain
{

class PosiotionableDraft final : public IPositionableDraft
{
private:
	using Positionables = std::vector<Positionable>;

	using SignalPositionableAdded = illusio::common::signal<void(size_t)>;
	using SignalPositionableRemoved = illusio::common::signal<void(size_t, IPositionable&)>;

	// <<interface>> IPositionableDraft
	void Insert(const Positionable& positionable, std::optional<size_t> index = std::nullopt) override;
	void Remove(std::optional<size_t> index = std::nullopt) override;

	Positionable GetPositionable(size_t index) override;
	size_t GetPositionableCount() const noexcept override;

	Connection DoOnPositionableInsert(const OnPositionableInsert& handler) override;
	Connection DonOnPositionableRemove(const OnPositionableRemove& handler) override;
	// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	Positionables m_positionables;

	SignalPositionableAdded m_positionableAdded;
	SignalPositionableRemoved m_positionableRemoved;
};

} // namespace illusio::domain
