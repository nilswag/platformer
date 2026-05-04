#include <spdlog/spdlog.h>

#include "app.h"
#include "math/math.h"

int main()
{
#ifdef _DEBUG
	spdlog::set_level(spdlog::level::trace);
#endif
	App app;
	app.run();

	return 0;
}