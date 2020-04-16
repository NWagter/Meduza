#include "Sandbox.h"

#include <iostream>

int main()
{
	Sandbox* app = new Sandbox();

	app->Run();

	delete app;

	return 0;
}