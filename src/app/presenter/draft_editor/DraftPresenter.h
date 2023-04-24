#pragma once

#include "../IDocument.h"

#include "app/edit/manager/UndoManager.h"

namespace app::presenter
{

class DraftPresenter final : public IDocument
{
public:
	bool CanUndo() const noexcept override;
	bool CanRedo() const noexcept override;

private:
	using UndoManager = edit::UndoManager;

	UndoManager m_undoManager;
};

} // namespace app::presenter
