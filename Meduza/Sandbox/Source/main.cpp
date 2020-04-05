#include "Sandbox.h"

#include <iostream>

int main()
{
	Sandbox* app = new Sandbox();

	app->Run();

	delete app;

	std::cin.get();

	return 0;
}