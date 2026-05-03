#include <spdlog/spdlog.h>

#include "gfx/window.h"

int main()
{
#ifdef _DEBUG
	spdlog::set_level(spdlog::level::debug);
#endif

	Window window(800, 800, "platformer");

	return 0;
}