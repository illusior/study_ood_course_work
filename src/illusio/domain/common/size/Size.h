#pragma once

namespace illusio::domain::common::axes
{

template <typename T>
struct Size
{
	explicit constexpr Size() = default;
	explicit constexpr Size(T width, T height);

	constexpr bool operator==(const Size<T>& other) const noexcept;
	constexpr bool operator!=(const Size<T>& other) const noexcept;

	T width, height;
};

template <typename T>
void TryCheckSizeIsValid(const Size<T>& size);

} // namespace illusio::domain::common::axes
