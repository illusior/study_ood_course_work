#pragma once

#include "../IStyle.h"

namespace illusio::domain::common::style
{

class Style : public IStyle
{
public:
	constexpr explicit Style() = default;
	constexpr explicit Style(RGBAColor color);

	constexpr RGBAColor GetColor() const noexcept override;
	constexpr void SetColor(RGBAColor color) override;

	constexpr bool operator==(const IStyle& other) const override;
	constexpr bool operator!=(const IStyle& other) const override;

private:
	RGBAColor m_rgbaColor = 0;
};

} // namespace illusio::domain::common::style
