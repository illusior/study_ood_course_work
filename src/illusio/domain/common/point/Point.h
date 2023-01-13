#pragma once

namespace illusio::domain::common::axes
{

template <typename T>
struct Point
{
	explicit constexpr Point() = default;
	template <typename T>
	explicit constexpr Point(T x, T y)
		: x(x)
		, y(y)
	{
	}

	constexpr T Distance(const Point& other) const noexcept;

	constexpr bool operator==(const Point& other) const noexcept;
	constexpr bool operator!=(const Point& other) const noexcept;

	T x, y;
};

} // namespace illusio::domain::common::axes
