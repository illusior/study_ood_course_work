#pragma once

#include "../../imgui/WindowImGui.h"

namespace app::window
{

class WDraftEditorImGui final : public WindowImGui
{
public:
	using MyBase = WindowImGui;

	explicit constexpr WDraftEditorImGui()
		: MyBase("Draft Editor")
	{
	}

private:
	// <<abstract>> BaseWindow
	bool Begin() override;
	void End() override;
	// >>>>>>>>>>>>>>>>>>>>>>

	// <<abstract>> WindowImGui
	void RenderContent() override;
	// >>>>>>>>>>>>>>>>>>>>>

	bool m_isGridEnabled = true;
	ImVec2 m_scrolling = ImVec2(0, 0);
};

} // namespace app::window
