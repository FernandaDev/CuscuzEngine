
#include <iostream>
#include "Engine.h"


int main(int agrc, char* argv[])
{
	Engine* app = new Engine();
	app->Run();
	delete app;

	return 0;
}