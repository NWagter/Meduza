#include "Sandbox.h"
#ifdef DEBUG
#include <vld.h>
#endif // DEBUG



int main() {

	Sandbox app = Sandbox(true);

	app.Run();
}