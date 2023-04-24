#pragma once

#include <GLFW/glfw3.h>

namespace app::window
{

class ImGuiBackends
{
public:
	// clang-format off
	// use tags to overload methods
	struct using_glfw_opengl3 {};
	// clang-format on

	// GLFW + OpenGL3
	static void Init(GLFWwindow*& window);
	static void DeInit(GLFWwindow* window);
	static void DrawBegin(using_glfw_opengl3);
	static void DrawEnd(GLFWwindow* window);
	// GLFW + OpenGL3
};

} // namespace app::window
