#include <iostream>
#include "util/log.h"

int main()
{
	logger::debug("Hello {}!", "Debug");
	logger::trace("Hello Trace!");
	logger::info("Hello Info!");
	logger::warning("Hello Warning!");
	logger::error("Hello Error!");

	return 0;
}