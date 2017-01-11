#include "Windows.h"
#include "SList.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR commandLine, int showCommand)
{
	auto list = new SList();
	auto data = list->getData();
	delete(list);
	return 0;
}
