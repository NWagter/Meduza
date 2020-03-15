#include "pch.h"
#include "Sandbox.h"

#ifdef _DEBUG
#include <vld.h>
#endif // DEBUG

int main()
{
	Sandbox* app = new Sandbox();

	app->Run();

	delete app;
}