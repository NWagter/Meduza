#include "PCH.h"
#include "Application.h"

int main()
{
	Application app = Application();

	app.Run();
	app.Destroy();
	
	return 0;
}