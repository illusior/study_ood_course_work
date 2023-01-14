#pragma once

#include <memory>

namespace app::edit
{

class IUndoableEdit;

using IUndoableEditRawPtr = IUndoableEdit*;
using IUndoableEditPtr = std::unique_ptr<IUndoableEdit>;
using IUndoableEditSharedPtr = std::shared_ptr<IUndoableEdit>;

} // namespace app::edit
