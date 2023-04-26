#include "pch_illusio.h"

#include "Style.h"

namespace illusio::domain::common::style
{

Style::Style(RGBAColor color)
	: m_rgbaColor(color)
{
}

using RGBAColor = Style::RGBAColor;

RGBAColor Style::GetColor() const noexcept
{
	return m_rgbaColor;
}

void Style::SetColor(RGBAColor color)
{
	m_rgbaColor = color;
}

bool Style::operator==(const IStyle& other) const
{
	return m_rgbaColor == other.GetColor();
}

bool Style::operator!=(const IStyle& other) const
{
	return !(*this == other);
}

} // namespace illusio::domain::common::style
