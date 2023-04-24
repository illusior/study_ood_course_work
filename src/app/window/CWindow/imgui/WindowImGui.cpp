#include "pch.h"

#include "WindowImGui.h"

namespace app::window
{

void WindowImGui::Update()
{
	if (Begin())
	{
		RenderContent();
		End();
	}
}

bool WindowImGui::Begin()
{
	if (!IsOpen())
	{
		return false;
	}
	return ImGui::Begin(m_title.data());
}

void WindowImGui::End()
{
	ImGui::End();
}

} // namespace app::window
