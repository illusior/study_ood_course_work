#include "pch.h"

#include "BaseWindow.h"

namespace app::window
{

BaseWindow::BaseWindow(Title title)
	: m_title(title)
	, m_isOpen(true)
{
}

BaseWindow::Title BaseWindow::GetTitle() const noexcept
{
	return m_title;
}

bool BaseWindow::IsOpen() const noexcept
{
	return m_isOpen;
}

bool BaseWindow::Init()
{
	if (m_isInited)
	{
		return false;
	}

	m_isInited = Initialize();

	return m_isInited;
}

void BaseWindow::Update()
{
	Init();
}

bool BaseWindow::Close() noexcept
{
	auto wasOpen = m_isOpen;
	m_isOpen = false;
	return wasOpen;
}

bool BaseWindow::Initialize()
{
	return false;
}

} // namespace app::window
