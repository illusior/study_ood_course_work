#pragma once

#include <vector>

#include "../IUndoableCompoundEdit.h"

#include "../../AbstractUndoableEdit.h"

namespace app::edit
{

class CompoundEdit : public AbstractUndoableEdit
{
public:
	using MyBase = AbstractUndoableEdit;

	// <<interface>> IUndoableCompoundEdit
	bool AddEdit(const Edit& edit) final;
	// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	bool EndCompose() noexcept;

protected:
	explicit CompoundEdit() = default;

	// <<interface>> AbstractUndoableEdit
	bool DerivedExecute() override;
	bool DerivedUndo() override;
	bool DerivedRedo() override;
	// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	using Edits = std::vector<Edit>;

	Edits m_edits;

private:

	bool m_inCompose = true;
};

} // namespace app::edit
