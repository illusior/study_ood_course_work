#pragma once

#include "IUndoableEdit_fwd.h"

namespace app::edit
{

class IUndoableEdit
{
public:
	virtual void Execute() = 0;

	virtual void Undo() = 0;
	virtual void Redo() = 0;

	virtual bool CanUndo() const = 0;
	virtual bool CanRedo() const = 0;

	virtual void Destroy() = 0;

	using Edit = IUndoableEditSharedPtr;
	virtual bool AddEdit(const Edit& edit) = 0;
	virtual bool ReplaceEdit(const Edit& edit) = 0;

	virtual void operator()() = 0;

	virtual ~IUndoableEdit() = default;
};

} // namespace app::edit
