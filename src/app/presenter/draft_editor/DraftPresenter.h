#pragma once

#include <app/window/CWindow/draft_editor/imgui/WDraftEditorImGui.h>

#include "../IDocument.h"

#include "app/edit/manager/UndoManager.h"

namespace app::presenter
{

class DraftPresenter final : public IDocument
{
public:
	using View = window::WDraftEditorImGui*;
	explicit DraftPresenter(View windowDraft);

	// <<interface>> IDocument
	void AddShape(ShapeType shapeType, const Point& startPoint, const Size& size) override;

	IDocument::PositionableGroup GetPositionableGroup() const override;

	UuidOpt GetUuidOfPositionableAtPoint(const Point& p) override;
	void SelectPositionable(const UuidOpt& uuid) override;
	const FrameOpt& GetSelectionFrame() const noexcept override;

	bool CanUndo() const noexcept override;
	bool CanRedo() const noexcept override;
	// >>>>>>>>>>>>>>>>>>>>>>>

private:
	using UndoManager = edit::UndoManager;
	UndoManager m_undoManager;

	using PositionableGroup = illusio::domain::IPositionableGroupSharedPtr;
	PositionableGroup m_positionableDraft;

	View m_view;
};

} // namespace app::presenter
