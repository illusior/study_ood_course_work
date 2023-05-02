#pragma once

#include <ranges>
#include <vector>

#include "../../PositionableImpl.hpp"
#include "../IPositionableGroup.h"

namespace illusio::domain
{

template <typename IBase = IPositionableGroup>
class PositionableGroup : public PositionableImpl<IBase>
	, private std::enable_shared_from_this<PositionableGroup<IBase>>
{
	// clang-format off
	// search for passKey idiom: when ctor is hidden for std::make_shared
	struct pass_key { explicit constexpr pass_key() {} };
	// clang-format on

public:
	using MyBasePositionable = PositionableImpl<IBase>;

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
	using PointD = typename IBase::PointD;
	IPositionableSharedPtr GetPositionableAtPoint(const PointD& p) override
	{
		auto idx = _GetPositionableAtPointIndex(p);
		return (idx.has_value() ? m_positionables[*idx] : nullptr);
	}

	IPositionableSharedConstPtr GetPositionableAtPoint(const PointD& p) const override
	{
		auto idx = _GetPositionableAtPointIndex(p);
		return (idx.has_value() ? m_positionables[*idx] : nullptr);
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

	void SetFrame(const FrameD& frame) final
	{// frame - пришёл новый selectionFrame
		auto currFrame = GetFrame();

		auto coefX = frame.size.width / currFrame.size.width;
		auto coefY = frame.size.height / currFrame.size.height;

		bool moveTurnX = // clang-format off
			frame.pLeftTop.x > currFrame.pLeftTop.x;
		bool moveTurnY = // clang-format off
			frame.pLeftTop.y > currFrame.pLeftTop.y; // clang-format on

		for (auto& positionable : m_positionables)
		{
			auto posFrame = positionable->GetFrame();
			auto distanceX = posFrame.pLeftTop.x - currFrame.pLeftTop.x;
			auto distanceY = posFrame.pLeftTop.y - currFrame.pLeftTop.y;

			auto newPositionableFrame = FrameD{
				frame.pLeftTop.x + distanceX * coefX,
				frame.pLeftTop.y + distanceY * coefY,
				posFrame.size.width * coefX,
				posFrame.size.height * coefY
			};

			positionable->SetFrame(newPositionableFrame);
		}
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

		for (const auto& positionable : m_positionables)
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

	std::optional<size_t> GetPositionableIndex(const IPositionableSharedPtr& positionable) const noexcept final
	{
		auto itBeg = m_positionables.begin();
		auto it = std::find(itBeg, m_positionables.end(), positionable);
		if (it == m_positionables.end())
		{
			return std::nullopt;
		}
		return std::distance(itBeg, it);
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

		event::DomainPositionableModelEvent evt{};
		evt.EventType = event::DomainPositionableModelEventTypes::InsertPositionable;
		evt.PositionableChangedAtIndexInGroup = insertIndex;
		evt.PositionableEventInitiator = positionable.get();
		evt.PositionablesGroup = this;
		this->EmitChangeSignal(evt);
	}

	void RemovePositionable(size_t index) override
	{
		if (index >= m_positionables.size())
		{
			throw std::out_of_range("[illusio][domain] Failed to remove Positionable at " + std::to_string(index) + " index. Index is out of range");
		}

		auto it = m_positionables.begin();
		std::advance(it, index);

		auto& erasing = *it;
		m_positionables.erase(it);

		event::DomainPositionableModelEvent evt{};
		evt.EventType = event::DomainPositionableModelEventTypes::RemovePositionable;
		evt.PositionableChangedAtIndexInGroup = index;
		evt.PositionableEventInitiator = erasing.get();
		evt.PositionablesGroup = this;
		this->EmitChangeSignal(evt);
	}

	void MovePositionableToIndex(size_t positionableAt, size_t to) final
	{
		auto posCount = m_positionables.size();
		if (posCount <= 1)
		{
			return;
		}

		if (positionableAt >= posCount || to >= posCount)
		{
			throw std::out_of_range("[illusio][domain] Failed to move Positionable at " + std::to_string(positionableAt) + " index. Index is out of range");
		}

		auto turn = (positionableAt < to);
		for (size_t i = positionableAt; (turn ? i < to : i > to); i = (turn ? ++i : --i))
		{
			m_positionables[i].swap(m_positionables[(turn ? i + 1 : i - 1)]);
			if (!turn && i - 1 == 0)
			{
				break;
			}
		}

		event::DomainPositionableModelEvent evt{};
		evt.EventType = event::DomainPositionableModelEventTypes::Rearranged;
		evt.PositionableChangedAtIndexInGroup = to;
		evt.PositionableEventInitiator = m_positionables[to].get();
		evt.PositionablesGroup = this;
		this->EmitChangeSignal(evt);
	}
	// >>>>>>>>>>>>>>>>>>>>>

protected:
	using Connection = typename IBase::Connection;

	explicit constexpr PositionableGroup()
		: m_positionables()
	{
	}

private:
	std::optional<size_t> _GetPositionableAtPointIndex(const PointD& p) const
	{
		size_t i = GetPositionablesCount() - 1;
		for (auto& positionable : m_positionables | std::views::reverse)
		{
			if (positionable->IsPositionableContainsPoint(p))
			{
				return i;
			}
			if (i == 0)
			{
				break;
			}
			--i;
		}

		return std::nullopt;
	}

	using PositionablesContainer = std::vector<IPositionableSharedPtr>;
	PositionablesContainer m_positionables;
};

} // namespace illusio::domain
