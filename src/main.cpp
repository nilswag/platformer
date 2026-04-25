#include "gfx/window.h"
#include "gfx/renderer.h"

int main()
{
	Window& window = Window::getInstance();

	Renderer& renderer = Renderer::getInstance();

	window.loop();

	return 0;
}