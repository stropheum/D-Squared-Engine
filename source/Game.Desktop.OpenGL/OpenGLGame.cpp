#include "Windows.h"
#include "SList.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR commandLine, int showCommand)
{
	SList::getData();
	return 0;
}
