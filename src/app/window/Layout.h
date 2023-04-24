#pragma once

#include <GLFW/glfw3.h>

#include "manager/IWindowManager.h"

namespace app::window
{

void DefaultLayout(IWindowManager& windowManager, GLFWwindow* window);

} // namespace app::window
