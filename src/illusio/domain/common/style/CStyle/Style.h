#pragma once

#include "../IStyle.h"

namespace illusio::domain::common::style
{

class Style : public IStyle
{
public:
	constexpr explicit Style() = default;
	constexpr explicit Style(RGBAColor color);

	RGBAColor GetColor() const noexcept override;
	void SetColor(RGBAColor color) override;

	bool operator==(const IStyle& other) const override;
	bool operator!=(const IStyle& other) const override;

private:
	RGBAColor m_rgbaColor = 0;
};

} // namespace illusio::domain::common::style
