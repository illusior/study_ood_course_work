#include "pch.h"

#include "AbstractUndoableEdit.h"

namespace app::edit
{

AbstractUndoableEdit::~AbstractUndoableEdit()
{
	Destroy();
}

void AbstractUndoableEdit::operator()()
{
	Execute();
}

void AbstractUndoableEdit::Execute()
{
	if (m_wasExecuted)
	{
		return;
	}

	m_wasExecuted = DerivedExecute();
}

void AbstractUndoableEdit::Undo()
{
	if (!CanUndo())
	{
		return;
	}

	m_wasExecuted = !DerivedUndo();
}

void AbstractUndoableEdit::Redo()
{
	if (!CanRedo())
	{
		return;
	}

	m_wasExecuted = DerivedRedo();
}

bool AbstractUndoableEdit::CanUndo() const
{
	return m_wasExecuted;
}

bool AbstractUndoableEdit::CanRedo() const
{
	return !CanUndo();
}

void AbstractUndoableEdit::Destroy()
{
}

bool AbstractUndoableEdit::AddEdit(const Edit& edit)
{
	return false;
}

bool AbstractUndoableEdit::ReplaceEdit(const Edit& edit)
{
	return false;
}

} // namespace app::edit
