#pragma once

namespace illusio::domain::common::axes
{

constexpr auto WIDTH_IS_INVALID_MSG = "[Illusio] Error. Size has negative width";
constexpr auto HEIGHT_IS_INVALID_MSG = "[Illusio] Error. Size has negative height";

template <typename T>
struct Size
{
	explicit constexpr Size() = default;
	explicit constexpr Size(T width, T height)
		: width(width)
		, height(height)
	{
		if (width < 0)
		{
			throw std::logic_error(WIDTH_IS_INVALID_MSG);
		}
		if (height < 0)
		{
			throw std::logic_error(HEIGHT_IS_INVALID_MSG);
		}
	}

	constexpr bool operator==(const Size<T>& other) const noexcept
	{
		return width == other.width && height == other.height;
	}

	constexpr bool operator!=(const Size<T>& other) const noexcept
	{
		return !(*this == other);
	}

	T width, height;
};

} // namespace illusio::domain::common::axes
