#pragma once

#include <functional>

#include "Style.h"

namespace illusio::domain::common::style
{

class StyleComposite : public Style
{
public:
	using Enumerator = std::function<void(std::function<void(Style&)>)>;

	explicit constexpr StyleComposite() = default;
};

} // namespace illusio::domain::common::style
