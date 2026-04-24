#include "gfx/window.h"

int main()
{
	Window& window = Window::getInstance();
	window.loop();

	return 0;
}