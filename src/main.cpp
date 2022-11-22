#include "stdio.h"

#pragma warning(push)
#pragma warning(disable:4312)
#pragma warning(disable:4311)
#include <Fl/Fl.h>
#pragma warning(pop)

#include"GameWindow.h"

int main(int, char**)
{
	printf("Let's physics~(^)o(^)\n");

	GameWindow gw;
	
	gw.show();

	Fl::run();
}