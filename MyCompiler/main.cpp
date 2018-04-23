#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <crtdbg.h>
#include "UnitTest.h"

int main()
{
	_CrtDumpMemoryLeaks();
	return 0;
}