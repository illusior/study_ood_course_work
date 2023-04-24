#pragma once

#include <vector>

#include "../../IWindowManager.h"

#include <GLFW/glfw3.h>

namespace app::window
{

class WindowManagerImGui final : public IWindowManager
{
public:
	explicit WindowManagerImGui();
	~WindowManagerImGui();

private:
	// <<interface>> IWindowManager
	void Update() override;
	void Render() override;

	void AddWindow(Window&& window) override;
	// >>>>>>>>>>>>>>>>>>>>>>>>>>>>

	using Windows = std::vector<Window>;
	Windows m_windows;
};

} // namespace app::window
