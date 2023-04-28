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
	using UuidOpt = typename IBase::UuidOpt;
	using PointD = typename IBase::PointD;
	UuidOpt GetUuidOfPositionableAtPoint(const PointD& point)
	{
		for (auto& positionable : m_positionables)
		{
			auto res = positionable->GetUuidOfPositionableAtPoint(point);
			if (res.has_value())
			{
				return res;
			}
		}

		return std::nullopt;
	}

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

	void SetFrame(const FrameD&) final
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

	using Canvas = typename IBase::Canvas;
	void AddToCanvas(Canvas canvas) const override
	{
		if (canvas == nullptr)
		{
			throw std::runtime_error("[illusio][PositionableGroup] Can't draw positionables at canvas. Null given");
		}

		auto positionablesCopy = m_positionables;
		for (const auto& positionable : positionablesCopy)
		{
			positionable->AddToCanvas(canvas);
		}
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

	void InsertPositionable(const IPositionableSharedPtr& positionable, std::optional<size_t> index = std::nullopt) override
	{
		if (std::addressof(*positionable) == this)
		{
			return;
		}

		const auto insertIndex = (index.has_value())
			? std::min(*index, m_positionables.size())
			: m_positionables.size();

		auto it = m_positionables.begin();
		std::advance(it, insertIndex);

		m_positionables.insert(it, positionable);

		this->EmitChangeSignal();
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

		this->EmitChangeSignal();
	}
	// >>>>>>>>>>>>>>>>>>>>>

	// <<interface>> IPositionableGroup
	using UuidOpt = typename IBase::UuidOpt;
	void SelectPositionable(const UuidOpt& uuid) override
	{
		if (!uuid.has_value())
		{
			m_selectionFrame = std::nullopt;
			return;
		}

		if (this->GetUuid() == uuid)
		{
			m_selectionFrame = GetFrame();
		}

		for (auto& positionable : m_positionables)
		{
			if (positionable->GetUuid() == uuid)
			{
				m_selectionFrame = positionable->GetFrame();
			}
			if (auto posWithNestedPos = positionable->GetPositionableGroup())
			{
				posWithNestedPos->SelectPositionable(uuid);
				m_selectionFrame = posWithNestedPos->GetSelectionFrame();
			}
		}
	}

	using FrameOpt = typename IBase::FrameOpt;
	const FrameOpt& GetSelectionFrame() const noexcept
	{
		return m_selectionFrame;
	}
	// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

protected:
	using Connection = typename IBase::Connection;

	explicit constexpr PositionableGroup()
		: m_positionables()
	{
	}

private:
	using OnFrameChange = typename IBase::OnFrameChange;
	Connection DoOnFrameChange(const OnFrameChange&) final
	{// TODO: see IPositionableGroup.h
		return Connection();
	}

	using PositionablesContainer = std::vector<IPositionableSharedPtr>;
	PositionablesContainer m_positionables;

	FrameOpt m_selectionFrame;
};

} // namespace illusio::domain
