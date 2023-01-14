#pragma once

#include <memory>

namespace app::edit
{

class IUndoableCompoundEdit;

using IUndoableCompoundEditRawPtr = IUndoableCompoundEdit*;
using IUndoableCompoundEditPtr = std::unique_ptr<IUndoableCompoundEdit>;
using IUndoableCompoundEditSharedPtr = std::shared_ptr<IUndoableCompoundEdit>;

} // namespace app::edit
