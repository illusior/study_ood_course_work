#include "pch_illusio.h"

#include "Style.h"

namespace illusio::domain::common::style
{

constexpr Style::Style(RGBAColor color)
	: m_rgbaColor(color)
{
}

using RGBAColor = Style::RGBAColor;

constexpr RGBAColor Style::GetColor() const noexcept
{
	return m_rgbaColor;
}

constexpr void Style::SetColor(RGBAColor color)
{
	m_rgbaColor = color;
}

constexpr bool Style::operator==(const IStyle& other) const
{
	return m_rgbaColor == other.GetColor();
}

constexpr bool Style::operator!=(const IStyle& other) const
{
	return !(*this == other);
}

} // namespace illusio::domain::common::style
