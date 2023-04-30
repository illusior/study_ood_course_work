#pragma once

#include "../CEdit/compound/CUndoableCompoundEdit/CompoundEdit.h"

namespace app::edit
{

class UndoManager : private CompoundEdit
{
public:
	// <<interface>> IUndoableEdit
	using IUndoableEdit::Undo;
	using IUndoableEdit::Redo;

	bool CanUndo() const final;
	bool CanRedo() const final;
	// >>>>>>>>>>>>>>>>>>>>>>>>>>>

	void AddAndExecuteEdit(const Edit& edit);

private:
	// <<interface>> AbstractUndoableEdit
	bool DerivedExecute() final;
	bool DerivedUndo() final;
	bool DerivedRedo() final;
	// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	size_t m_nextEditIndex = 0;
};

} // namespace app::edit
