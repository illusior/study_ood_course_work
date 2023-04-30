﻿#pragma once

#include <algorithm>

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
	T maxX = std::numeric_limits<T>::min();
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

} // namespace illusio::domain::common::axes
