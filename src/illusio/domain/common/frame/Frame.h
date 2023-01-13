#pragma once

#include "../point/Point.h"
#include "../size/Size.h"

namespace illusio::domain::common::axes
{

template <typename T>
struct Frame
{
	explicit constexpr Frame() = default;
	explicit constexpr Frame(const Point<T>& leftTop, const Size<T>& size);
	explicit constexpr Frame(T xLeftTop, T yLeftTop, T width, T height);

	constexpr bool operator==(const Frame<T>& other) const noexcept;
	constexpr bool operator!=(const Frame<T>& other) const noexcept;

	Point<T> pLeftTop;
	Size<T> size;
};

template <typename T, typename Container>
Frame<T> GetMaxFrame(const Container& framesContainer);

} // namespace illusio::domain::common::axes
