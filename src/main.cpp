#include "gfx/window.h"

int main()
{
	Window window(800, 800, "platformer");
	window.loop();

	return 0;
}