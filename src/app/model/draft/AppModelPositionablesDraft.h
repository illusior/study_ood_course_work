#pragma once

#include <optional>

// #include <illusio/domain/common/frame/CFrame/FrameD.h>
#include <illusio/domain/object/positionable/group/CPositionableGroup/PositionableGroup.hpp>

#include <app/edit/manager/UndoManager.h>

#include "AppModelPositionablesDraft_fwd.h"

namespace app::model
{

class AppModelPositionablesDraft : public illusio::domain::PositionableGroup<illusio::domain::IPositionableGroup>
	, public edit::UndoManager
{
public:
	using MyBaseDomainModel = illusio::domain::PositionableGroup<illusio::domain::IPositionableGroup>;
	using MyBaseHistoryModel = edit::UndoManager;

	AppModelPositionablesDraft() = default;
};

} // namespace app::model
