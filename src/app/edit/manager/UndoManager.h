#pragma once

#include "../CEdit/compound/CUndoableCompoundEdit/CompoundEdit.h"

namespace app::edit
{

class UndoManager : private CompoundEdit
{
public:
	using IUndoableCompoundEdit::Undo;
	using IUndoableCompoundEdit::Redo;

	// <<interface>> IUndoableEdit
	bool CanUndo() const final;
	bool CanRedo() const final;
	// >>>>>>>>>>>>>>>>>>>>>>>>>>>

	void AddAndExecuteEdit(const Edit& edit);

private:
	// <<abstract>> AbstractUndoableEdit
	bool DerivedExecute() final;
	bool DerivedUndo() final;
	bool DerivedRedo() final;
	// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	size_t m_nextEditIndex = 0;
};

} // namespace app::edit
