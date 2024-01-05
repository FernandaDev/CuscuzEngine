
#include <iostream>
#include "Application.h"

int main(int agrc, char* argv[])
{
	Application* app{};
	app->Run();
	delete app;
}