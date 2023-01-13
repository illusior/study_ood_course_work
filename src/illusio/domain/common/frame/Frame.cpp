#include "pch_illusio.h"

#include "Frame.h"

namespace illusio::domain::common::axes
{

template <typename T>
inline constexpr Frame<T>::Frame(const Point<T>& leftTop, const Size<T>& size)
	: pLeftTop(leftTop)
	, size(size)
{
}

template <typename T>
constexpr Frame<T>::Frame(T xLeftTop, T yLeftTop, T width, T height)
	: pLeftTop(xLeftTop, yLeftTop)
	, size(width, height)
{
}

template <typename T>
constexpr bool Frame<T>::operator==(const Frame<T>& other) const noexcept
{
	return pLeftTop = other.pLeftTop && size == other.size;
}

template <typename T>
constexpr bool Frame<T>::operator!=(const Frame<T>& other) const noexcept
{
	return !(*this == other);
}

template <typename T, typename Container>
Frame<T> GetMaxFrame(const Container& framesContainer)
{
	T minX{}, minY{}, maxX{}, maxY{};

	for (const auto& rect : framesContainer)
	{
		minX = std::min(minX, rect.leftTop.x);
		minY = std::min(minY, rect.leftTop.y);

		maxX = std::max(maxX, rect.leftTop.x + rect.width);
		maxY = std::max(maxY, rect.leftTop.y + rect.height);
	}

	return Frame<T>(minX, minY, minX + maxX, minY + maxY);
}

} // namespace illusio::domain::common::axes
