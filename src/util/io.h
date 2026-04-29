#include <string>
#include <fstream>
#include <sstream>

#include "log.h"

inline std::string readFile(const char* path)
{
	logger::trace("Reading file with path {}.", path);
	std::string str;
	std::string line;

	std::ifstream f(path);
	if (!f.is_open())
	{
		logger::error("Error while opening file ({}).", path);
		return str;
	}

	while (std::getline(f, line))
		str += line + '\n';

	if (f.bad())
		logger::error("Error while reading file ({}).", path);

	return str;
}