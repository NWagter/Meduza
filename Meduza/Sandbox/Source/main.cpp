#include "Sandbox.h"


#ifdef DEV
#include <vld.h>
#endif // DEV


int main()
{
	Sandbox* app = new Sandbox();

	app->Run();

	delete app;
}