#include "Sandbox.h"

int main()
{
	Sandbox* app = new Sandbox();

	app->Run();

	delete app;
}