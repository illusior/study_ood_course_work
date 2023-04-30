#pragma once

#include <memory>

namespace app::model
{

class AppModelPositionablesDraft;

using AppModelPositionablesDraftRawPtr = AppModelPositionablesDraft*;

using AppModelPositionablesDraftPtr = std::unique_ptr<AppModelPositionablesDraft>;
using AppModelPositionablesDraftSharedPtr = std::shared_ptr<AppModelPositionablesDraft>;

} // namespace app::model
