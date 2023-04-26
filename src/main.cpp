#include "pch.h"

#include "app/Application.h"

int main()
{
	auto& appInstance = app::Application::GetInstance();
	appInstance.Start();

	return 0;
}
