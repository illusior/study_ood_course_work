#pragma once

#include "../IUndoableEdit.h"

namespace app::edit
{

class AbstractUndoableEdit : public IUndoableEdit
{
public:
	// <<interface>> IUndoableEdit
	void Execute() final;

	void Undo() override;
	void Redo() override;

	bool CanUndo() const override;
	bool CanRedo() const override;

	void Destroy() override;

	bool ReplaceEdit(const Edit& edit) override;

	void operator()() final;
	// >>>>>>>>>>>>>>>>>>>>>>>>>>

protected:
	explicit constexpr AbstractUndoableEdit() = default;
	~AbstractUndoableEdit();

	virtual bool DerivedExecute() = 0;

	virtual bool DerivedUndo() = 0;
	virtual bool DerivedRedo() = 0;

private:
	bool m_wasExecuted = false;
};

} // namespace app::edit
