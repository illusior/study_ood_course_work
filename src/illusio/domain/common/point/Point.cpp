#include "pch_illusio.h"

#include "Point.h"

namespace illusio::domain::common::axes
{

template <typename T>
inline constexpr T Point<T>::Distance(const Point& other) const noexcept
{
	return std::sqrt((other.x - x) * (other.x - x) + (other.y - y) * (other.y - y));
}

template <typename T>
constexpr bool Point<T>::operator==(const Point& other) const noexcept
{
	return x == other.x && y == other.y;
}

template <typename T>
constexpr bool Point<T>::operator!=(const Point& other) const noexcept
{
	return !(*this == other);
}

} // namespace illusio::domain::common::axes
