#pragma once

#include <SpringEngine/Core/Application.hpp>

#ifdef SE_PLATEFORM_WINDOWS

extern SE::Application* SE::createApp();

int main()
{
	SE::Application* app = SE::createApp();
	app->run();
	delete app;
	return 0;
}

#endif