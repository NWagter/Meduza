#include "Sandbox.h"

#include <iostream>

#include <vld.h>

int main()
{
	Sandbox* app = new Sandbox();

	app->Run();

	delete app;

	return 0;
}