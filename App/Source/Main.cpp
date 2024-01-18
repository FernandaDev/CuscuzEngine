#include "pch.h"
#include "Application.h"

int main(int agrc, char* argv[])
{
	Application* app = new Application();
	app->Run();
	delete app;

	return 0;
}