#include "pch_illusio.h"

#include "Size.h"

namespace illusio::domain::common::axes
{

template <typename T>
inline constexpr Size<T>::Size(T width, T height)
	: width(T())
	, height(T())
{
	TryCheckSizeIsValid(*this);
}

template <typename T>
constexpr bool Size<T>::operator==(const Size<T>& other) const noexcept
{
	return width == other.width && height == other.height;
}

template <typename T>
constexpr bool Size<T>::operator!=(const Size<T>& other) const noexcept
{
	return !(*this == other);
}

constexpr auto WIDTH_IS_INVALID_MSG = "[Illusio] Error. Size has negative width";
constexpr auto HEIGHT_IS_INVALID_MSG = "[Illusio] Error. Size has negative height";

template <typename T>
void TryCheckSizeIsValid(const Size<T>& size)
{
	if (size.width < 0)
	{
		throw std::logic_error(WIDTH_IS_INVALID_MSG);
	}
	if (size.height < 0)
	{
		throw std::logic_error(HEIGHT_IS_INVALID_MSG);
	}
}

} // namespace illusio::domain::common::axes
