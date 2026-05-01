#include "util/log.h"
#include "app.h"

int main()
{
#ifdef _DEBUG
	log().setLevel(LogLevel::TRACE);
#else
	log().setLevel(LogLevel::FATAL);
#endif

	App app;
	app.run();

	return 0;
}