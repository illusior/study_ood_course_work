#pragma once

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
		auto maxY = pLeftTop.y + size.height;
		return (std::min(p.x, pLeftTop.x) == pLeftTop.x && std::max(p.y, maxY) == maxY);
	}

	constexpr bool operator==(const Frame<T>& other) const noexcept
	{
		return pLeftTop = other.pLeftTop && size == other.size;
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
	T minX{}, minY{}, maxX{}, maxY{};

	for (const auto& rect : framesContainer)
	{
		minX = std::min(minX, rect.pLeftTop.x);
		minY = std::min(minY, rect.pLeftTop.y);

		maxX = std::max(maxX, rect.pLeftTop.x + rect.size.width);
		maxY = std::max(maxY, rect.pLeftTop.y + rect.size.height);
	}

	return Frame<T>(minX, minY, std::abs(minX + maxX), std::abs(minY + maxY));
}

} // namespace illusio::domain::common::axes
