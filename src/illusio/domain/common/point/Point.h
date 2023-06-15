#pragma once

#include <cmath>

namespace illusio::domain::common::axes
{

template <typename T>
struct Point
{
	explicit constexpr Point() = default;
	template <typename vT>
	explicit constexpr Point(vT x, vT y)
		: x(x)
		, y(y)
	{
	}

	constexpr T Distance(const Point& other) const noexcept
	{
		return std::sqrt((other.x - x) * (other.x - x) + (other.y - y) * (other.y - y));
	}

	bool operator==(const Point& other) const noexcept
	{
		return x == other.x && y == other.y;
	}

	constexpr bool operator!=(const Point& other) const noexcept
	{
		return !(*this == other);
	}

	T x, y;
};

} // namespace illusio::domain::common::axes
