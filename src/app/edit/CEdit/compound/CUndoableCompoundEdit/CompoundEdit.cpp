#include "pch.h"

#include "CompoundEdit.h"

namespace app::edit
{

bool CompoundEdit::AddEdit(const Edit& edit)
{
	if (!m_inCompose || std::is_same_v<decltype(*this), decltype(*edit)>)
	{
		return false;
	}

	if (m_edits.empty())
	{
		m_edits.push_back(edit);
		return true;
	}

	if (auto& lastEdit = m_edits.back())
	{
		if (auto lastCompoundEdit = std::dynamic_pointer_cast<IUndoableCompoundEdit>(lastEdit);
			lastCompoundEdit != nullptr && !lastCompoundEdit->AddEdit(edit))
		{
			if (edit->ReplaceEdit(lastEdit))
			{
				m_edits.pop_back();
			}
			m_edits.push_back(edit);
		}
	}

	return true;
}

bool CompoundEdit::EndCompose() noexcept
{
	bool result = m_inCompose;
	m_inCompose = false;

	return result;
}

bool CompoundEdit::DerivedExecute()
{
	std::for_each(m_edits.begin(), m_edits.end(), [](auto& edit) {
		edit->Execute();
	});
	return true;
}

bool CompoundEdit::DerivedUndo()
{
	std::for_each(m_edits.rbegin(), m_edits.rend(), [](auto& edit) {
		edit->Undo();
	});
	return true;
}

bool CompoundEdit::DerivedRedo()
{
	std::for_each(m_edits.begin(), m_edits.end(), [](auto& edit) {
		edit->Redo();
	});
	return true;
}

} // namespace app::edit
