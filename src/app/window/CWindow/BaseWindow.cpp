#include "pch.h"

#include "BaseWindow.h"

namespace app::window
{

BaseWindow::~BaseWindow()
{
	Close();
}

BaseWindow::Title BaseWindow::GetTitle() const noexcept
{
	return m_title;
}

bool BaseWindow::IsOpen() const noexcept
{
	return m_isOpen;
}

bool BaseWindow::Close() noexcept
{
	auto wasOpen = m_isOpen;
	m_isOpen = false;
	return wasOpen;
}

} // namespace app::window
