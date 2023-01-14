#pragma once

#include "IStyle_fwd.h"

#include "domain/common/color/RGBAColor.h"

namespace illusio::domain::common::style
{

class IStyle
{
public:
	using RGBAColor = color::RGBAColor;

	virtual RGBAColor GetColor() const noexcept = 0;
	virtual void SetColor(RGBAColor color) = 0;

	virtual bool operator==(const IStyle& other) const = 0;
	virtual bool operator!=(const IStyle& other) const = 0;

	virtual ~IStyle() = default;
};

} // namespace illusio::domain::common::style
