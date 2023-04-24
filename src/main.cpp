#include "pch.h"

#include "app/Application.h"

#include "domain/object/positionable/group/CPositionableGroup/PositionableDraft.h"
#include "domain/object/positionable/shape/solid/CShapeSolid/rectangle/CRectangle/Rectangle.h"

int main()
{
	auto& appInstance = app::Application::GetInstance();
	appInstance.Start();

	return 0;
}
