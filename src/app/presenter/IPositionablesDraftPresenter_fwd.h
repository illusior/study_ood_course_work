#pragma once

#include <memory>

namespace app::presenter
{

class IPositionablesDraftPresenter;

using IPositionablesDraftPresenterRawPtr = IPositionablesDraftPresenter*;
using IPositionablesDraftPresenterPtr = std::unique_ptr<IPositionablesDraftPresenter>;
using IPositionablesDraftPresenterSharedPtr = std::shared_ptr<IPositionablesDraftPresenter>;

} // namespace app::presenter
