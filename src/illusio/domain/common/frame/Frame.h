﻿#pragma once

#include <algorithm>
#include <vector>

#include "../point/Point.h"
#include "../size/Size.h"

namespace illusio::domain::common::axes
{

template <typename T>
struct Frame
{
	using DimensionType = T;

	explicit constexpr Frame() = default;
	explicit constexpr Frame(const Point<T>& leftTop, const Size<T>& size)
		: pLeftTop(leftTop)
		, size(size)
	{
	}

	explicit constexpr Frame(T xLeftTop, T yLeftTop, T width, T height)
		: pLeftTop(xLeftTop, yLeftTop)
		, size(width, height)
	{
	}

	constexpr bool ContainsPoint(const Point<T>& p) const noexcept
	{
		auto inX = (p.x >= pLeftTop.x) && (p.x <= pLeftTop.x + size.width);
		auto inY = (p.y >= pLeftTop.y) && (p.y <= pLeftTop.y + size.height);
		return inX && inY;
	}

	constexpr bool operator==(const Frame<T>& other) const noexcept
	{
		return pLeftTop == other.pLeftTop && size == other.size;
	}

	constexpr bool operator!=(const Frame<T>& other) const noexcept
	{
		return !(*this == other);
	}

	Point<T> pLeftTop;
	Size<T> size;
};

template <typename T, typename Container>
static inline Frame<T> GetMaxFrame(const Container& framesContainer)
{
	T minX = std::numeric_limits<T>::max();
	T minY = minX;
	T maxX = std::numeric_limits<T>::lowest();
	T maxY = maxX;

	for (const auto& rect : framesContainer)
	{
		minX = std::min(minX, rect.pLeftTop.x);
		minY = std::min(minY, rect.pLeftTop.y);

		maxX = std::max(maxX, rect.pLeftTop.x + rect.size.width);
		maxY = std::max(maxY, rect.pLeftTop.y + rect.size.height);
	}

	return Frame<T>(minX, minY, std::abs(maxX - minX), std::abs(maxY - minY));
}

template <typename T>
struct FrameStrider : Frame<T>
{
private:
	size_t m_pointCount;
	T m_padding;

	using Points = std::vector<Point<T>>;
	using Iterator = typename Points::iterator;
	Points m_points;

	void CalculatePointsEvenlyDistributedAtPerimeterOfFrame()
	{// TODO: tested only with 4 and 8 m_pointCount, padding not implemented
		auto& size = MyBase::size;
		auto& pLeftTop = MyBase::pLeftTop;

		auto perimeter = 2 * size.width + 2 * size.height;
		auto step = perimeter / m_pointCount;
		auto pointsAtX = size_t(std::round(size.width / step)) + (size.width <= size.height ? 1 : 0);
		auto pointsAtY = size_t(std::round(size.height / step)) + (size.height <= size.width ? 1 : 0);
		pointsAtX = pointsAtY = std::max(pointsAtX, pointsAtY);
		bool dimensionsAreSame = size.width == size.height;
		auto stepX = dimensionsAreSame ? step : size.width / (pointsAtX - 1);
		auto stepY = dimensionsAreSame ? step : size.height / (pointsAtY - 1);

		auto x = pLeftTop.x;
		auto y = pLeftTop.y;

		m_points.clear();
		m_points.reserve(m_pointCount);
		auto& framePointLT = pLeftTop;
		auto frameWidthX = framePointLT.x + size.width;
		auto frameHeightY = framePointLT.y + size.height;
		for (size_t i = 0; i < m_pointCount; ++i)
		{
			auto addingAtTop = (x < frameWidthX) && (y == framePointLT.y);
			auto addingAtRightSide = (x == frameWidthX) && (y < frameHeightY);
			auto addingAtBottom = (x <= frameWidthX) && (x > framePointLT.x) && (y == frameHeightY);
			auto addingAtLeftSide = (x == framePointLT.x) && (y <= frameHeightY);
			if (addingAtTop)
			{
				x = framePointLT.x + stepX * i;
			}
			else if (addingAtRightSide)
			{
				y = framePointLT.y + stepY * ((i + 1) % pointsAtY);
			}
			else if (addingAtBottom)
			{
				auto times = ((i - 1) % pointsAtX);
				x = frameWidthX - stepX * (times > 0 ? times : 1);
			}
			else if (addingAtLeftSide)
			{
				y = frameHeightY - stepY * (i % pointsAtY);
			}
			m_points.emplace_back(x, y); 
		}
	}

public:
	using MyBase = Frame<T>;
	explicit FrameStrider(const Frame<T>& frame, size_t pointsToGoOverAmount, T padding)
		: MyBase(frame)
		, m_pointCount(pointsToGoOverAmount)
		, m_padding(std::abs(padding))
	{
		CalculatePointsEvenlyDistributedAtPerimeterOfFrame();
	}

	constexpr auto begin() const { return m_points.begin(); }
	constexpr auto end() const { return m_points.end(); }
};

} // namespace illusio::domain::common::axes
