#pragma once

#include "../positionable/AppModelPositionable.h"
#include "illusio/domain/draft/IPositionableDraft.h"

namespace app::model
{

class AppModelDraft
{
public:
	AppModelPositionable& GetPositionable(size_t index) noexcept;
	size_t GetPositionablesCount() const noexcept;

private:
	using PositionablesDraft = illusio::domain::IPositionableDraftPtr;

	PositionablesDraft m_positionablesDraft;

};

} // namespace app::model
