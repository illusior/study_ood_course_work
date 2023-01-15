#pragma once

#include "../../IUndoableEdit.h"

namespace app::edit
{

class IUndoableCompoundEdit : public IUndoableEdit
{
public:
	// virtual bool AddEdit(const Edit& edit) = 0;

	virtual ~IUndoableCompoundEdit() = default;
};

} // namespace app::edit
