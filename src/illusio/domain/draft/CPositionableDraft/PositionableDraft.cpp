#include "pch_illusio.h"

#include "PositionableDraft.h"

namespace illusio::domain
{

void PosiotionableDraft::Insert(const Positionable& positionable, std::optional<size_t> index)
{
	const auto insertIndex = (index.has_value())
		? std::min(*index, GetPositionableCount())
		: GetPositionableCount();

	auto it = m_positionables.begin();
	std::advance(it, insertIndex);

	m_positionables.insert(it, positionable);

	m_positionableAdded(index.has_value() ? *index : GetPositionableCount() - 1);
}

void PosiotionableDraft::Remove(std::optional<size_t> index)
{
	const auto removeIndex = (index.has_value())
		? std::min(*index, GetPositionableCount() - 1)
		: GetPositionableCount();

	auto removingPositionable = GetPositionable(removeIndex);

	auto it = m_positionables.begin();
	std::advance(it, removeIndex);

	m_positionables.erase(it);

	m_positionableRemoved(removeIndex, *removingPositionable);
}

PosiotionableDraft::Positionable PosiotionableDraft::GetPositionable(size_t index)
{
	if (GetPositionableCount() == 0)
	{
		throw std::out_of_range("[PosiotionableDraft] Failed to get positionable");
	}

	const auto finalIndex = std::min(index, GetPositionableCount() - 1);

	return m_positionables[finalIndex];
}

size_t PosiotionableDraft::GetPositionableCount() const noexcept
{
	return m_positionables.size();
}

PosiotionableDraft::Connection PosiotionableDraft::DoOnPositionableInsert(const OnPositionableInsert& handler)
{
	return m_positionableAdded.connect(handler);
}

PosiotionableDraft::Connection PosiotionableDraft::DonOnPositionableRemove(const OnPositionableRemove& handler)
{
	return m_positionableRemoved.connect(handler);
}

} // namespace illusio::domain
