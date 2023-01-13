#pragma once

#include "IStyle_fwd.h"

#include "domain/common/color/RGBAColor.h"

namespace illusio::domain::common::style
{

class IStyle
{
public:
	using RGBAColor = color::RGBAColor;

	virtual constexpr RGBAColor GetColor() const noexcept = 0;
	virtual constexpr void SetColor(RGBAColor color) = 0;

	virtual constexpr bool operator==(const IStyle& other) const = 0;
	virtual constexpr bool operator!=(const IStyle& other) const = 0;

	virtual ~IStyle() = default;
};

} // namespace illusio::domain::common::style
