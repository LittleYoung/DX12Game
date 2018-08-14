#include "Test.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	Test test(hInstance);
	if (!test.Initialize()) { return 0; }
	return test.Run();
}