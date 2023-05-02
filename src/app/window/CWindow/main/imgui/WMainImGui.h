#pragma once

#include <functional>

#include <GLFW/glfw3.h>

#include <illusio/common/signals/signal.hpp>
#include <illusio/domain/object/positionable/shape/ShapeTypes.h>

#include "../../imgui/WindowImGui.h"

namespace app::window
{

class WMainImGui : public WindowImGui
{
public:
	using MyBase = WindowImGui;

	explicit WMainImGui(GLFWwindow* window);

	using Connection = illusio::common::connection;
	using OnGridToggleCallback = std::function<void()>;
	Connection DoOnGridToggle(const OnGridToggleCallback& handler);

	using ShapeType = illusio::domain::shape::ShapeType;
	using OnAddShapeCallback = std::function<void(ShapeType)>;
	Connection DoOnAddShape(const OnAddShapeCallback& handler);

	using OnRemoveShapeCallback = std::function<void()>;
	Connection DoOnRemoveShapeSelection(const OnRemoveShapeCallback& handler);

private:
	// <<abstract>> BaseWindow
	bool Begin() override;
	void End() override;
	// >>>>>>>>>>>>>>>>>>>>>>

	// <<abstract>> WindowImGui
	void RenderContent() final;
	// >>>>>>>>>>>>>>>>>>>>>>>>

	void HandleKeyboardInputs();

	GLFWwindow* m_window;

	bool m_isLightTheme = true; // otherwise is dark

	using GridToggleSignal = illusio::common::signal<void()>;
	GridToggleSignal m_gridToggleSignal;

	using AddShapeEventSignal = illusio::common::signal<void(ShapeType)>;
	AddShapeEventSignal m_addShapeSignal;

	using RemoveShapeEventSignal = illusio::common::signal<void()>;
	RemoveShapeEventSignal m_removeSelectedPositionablesSignal;
};

} // namespace app::window
