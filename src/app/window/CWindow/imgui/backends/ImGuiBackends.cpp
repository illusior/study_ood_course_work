#include "pch.h"

#include "ImGuiBackends.h"

namespace app::window
{

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

constexpr auto ERR_APPLICATION_WINDOW_CREATION_FAILED = "Failed to create application window";
constexpr auto APPLICATION_TITLE = "Illusio";

void ImGuiBackends::Init(GLFWwindow*& window)
{
	const auto isInitSuccess = glfwInit();

	const auto monitor = glfwGetPrimaryMonitor();
	const auto mode = glfwGetVideoMode(monitor);

	const auto appWidth = ILLUSIO_DEBUG == false ? mode->width : 1024;
	const auto appHeight = ILLUSIO_DEBUG == false ? mode->height: 720;

	// clang-format off
	window = glfwCreateWindow(appWidth,
		appHeight,
		APPLICATION_TITLE,
		ILLUSIO_DEBUG == false ? monitor : nullptr,
		NULL
	); // clang-format on

	if (!isInitSuccess || window == nullptr)
	{
		throw std::runtime_error(ERR_APPLICATION_WINDOW_CREATION_FAILED);
	}

	glfwSetErrorCallback(glfw_error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui::StyleColorsLight();

	ImGui_ImplOpenGL3_Init();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
}

void ImGuiBackends::DeInit(GLFWwindow* window)
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}

void ImGuiBackends::DrawBegin(using_glfw_opengl3)
{
	glfwPollEvents();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

constexpr auto CLEAR_COLOR = ImVec4(0, 0, 0, 1.00f);

void ImGuiBackends::DrawEnd(GLFWwindow* window)
{
	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(CLEAR_COLOR.x * CLEAR_COLOR.w, CLEAR_COLOR.y * CLEAR_COLOR.w, CLEAR_COLOR.z * CLEAR_COLOR.w, CLEAR_COLOR.w);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);
}

} // namespace app::window
