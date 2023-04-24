#include "pch.h"

#include "DraftPresenter.h"

namespace app::presenter
{

bool DraftPresenter::CanUndo() const noexcept
{
	return m_undoManager.CanUndo();
}

bool DraftPresenter::CanRedo() const noexcept
{
	return m_undoManager.CanRedo();
}

} // namespace app::presenter
