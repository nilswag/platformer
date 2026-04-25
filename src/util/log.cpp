#include <print>
#include "log.h"

Logger& Logger::getInstance()
{
	static Logger logger;
	return logger;
}

Logger::Logger()
{
	m_level = LogLevel::TRACE;
}

void Logger::log(LogLevel level, std::string_view tag, std::string_view msg) const
{
	if (level <= m_level)
	{
		std::println("{}{:<5} {:<15}  {}\033[0m",
			colorStr(level),
			levelStr(level),
			tag,
			msg
		);
	}
}

constexpr std::string_view Logger::levelStr(LogLevel level)
{
	switch (level)
	{
	case LogLevel::FATAL:   return "FATAL";
	case LogLevel::ERROR:   return "ERROR";
	case LogLevel::WARNING: return "WARN";
	case LogLevel::INFO:    return "INFO";
	case LogLevel::DEBUG:   return "DEBUG";
	case LogLevel::TRACE:   return "TRACE";
	default:			    return "?????";
	}
}

constexpr std::string_view Logger::colorStr(LogLevel level)
{
	switch (level)
	{
	case LogLevel::FATAL:   return "\033[31m";
	case LogLevel::ERROR:   return "\033[31m";
	case LogLevel::WARNING: return "\033[33m";
	case LogLevel::INFO:    return "\033[37m";
	case LogLevel::DEBUG:   return "\033[35m";
	case LogLevel::TRACE:   return "\033[36m";
	default:				return "\033[0m";
	}
}