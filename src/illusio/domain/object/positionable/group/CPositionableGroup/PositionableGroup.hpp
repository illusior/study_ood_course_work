#pragma once

#include <vector>

#include "../../PositionableImpl.hpp"
#include "../IPositionableGroup.h"

namespace illusio::domain
{

template <typename IBase = IPositionableGroup>
class PositionableGroup : public PositionableImpl<IBase>
	, public std::enable_shared_from_this<PositionableGroup<IBase>>
{
	// clang-format off
	// search for passKey idiom: when ctor is hidden for std::make_shared
	struct pass_key { explicit constexpr pass_key() {} };
	// clang-format on

public:
	using IPositionable = typename IBase::IPositionable;

	using FrameD = typename IBase::FrameD;

	static IPositionableGroupSharedPtr Create()
	{
		return std::make_shared<PositionableGroup>(pass_key{});
	}

	explicit constexpr PositionableGroup(pass_key)
		: m_positionables()
	{
	}

	// <<interface>> IPositionable
	FrameD GetFrame() const noexcept final
	{
		std::vector<FrameD> rects;
		rects.reserve(GetPositionablesCount());
		for (const auto& Positionable : m_positionables)
		{
			rects.push_back(Positionable->GetFrame());
		}

		return domain::common::axes::GetMaxFrame<typename FrameD::DimensionType>(rects);
	}

	void SetFrame(const FrameD& frame) final
	{
	}

	IPositionableGroupSharedPtr GetPositionableGroup() final
	{
		return this->shared_from_this();
	}

	IPositionableGroupSharedConstPtr GetPositionableGroup() const final
	{
		return this->shared_from_this();
	}
	// >>>>>>>>>>>>>>>>>>>>

	// <<interface>> IPositionables
	size_t GetPositionablesCount() const noexcept final
	{
		return m_positionables.size();
	}

	IPositionableSharedPtr GetPositionable(size_t index) final
	{
		if (index >= m_positionables.size())
		{
			throw std::out_of_range("[illusio][domain] Failed to get Positionable at" + std::to_string(index) + " index. Index is out of range");
		}

		auto it = m_positionables.begin();
		std::advance(it, index);

		return *it;
	}

	IPositionableSharedConstPtr GetPositionable(size_t index) const final
	{
		if (index >= m_positionables.size())
		{
			throw std::out_of_range("[illusio][domain] Failed to get Positionable at " + std::to_string(index) + " index. Index is out of range");
		}

		auto it = m_positionables.begin();
		std::advance(it, index);

		return *it;
	}

	void InsertPositionable(const IPositionableSharedPtr& Positionable, std::optional<size_t> index = std::nullopt) override
	{
		if (std::addressof(*Positionable) == this)
		{
			return;
		}

		const auto insertIndex = (index.has_value())
			? std::min(*index, m_positionables.size())
			: m_positionables.size();

		auto it = m_positionables.begin();
		std::advance(it, insertIndex);

		m_positionables.insert(it, Positionable);
	}

	void RemovePositionable(size_t index) override
	{
		if (index >= m_positionables.size())
		{
			throw std::out_of_range("[illusio][domain] Failed to remove Positionable at " + std::to_string(index) + " index. Index is out of range");
		}

		auto it = m_positionables.begin();
		std::advance(it, index);

		m_positionables.erase(it);
	}
	// >>>>>>>>>>>>>>>>>>>>>

protected:
	using Connection = typename IBase::Connection;

	explicit constexpr PositionableGroup()
		: m_positionables()
	{
	}

private:
	using OnFrameChange = typename IBase::OnFrameChange;

	using PositionablesContainer = std::vector<IPositionableSharedPtr>;

	// TODO: see IPositionableGroup.h
	Connection DoOnFrameChange(const OnFrameChange&) final
	{
		return Connection();
	}

	PositionablesContainer m_positionables;
};

} // namespace illusio::domain
