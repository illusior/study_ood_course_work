#include "pch.h"

#include "WindowImGui.h"

namespace app::window
{

WindowImGui::WindowImGui(Title title)
	: MyBase(title)
{
}

void WindowImGui::Update()
{
	MyBase::Update();

	if (Begin())
	{
		RenderContent();
		End();
	}
}

bool WindowImGui::Begin()
{
	return IsOpen() && ImGui::Begin(m_title.data());
}

void WindowImGui::End()
{
	ImGui::End();
}

} // namespace app::window
