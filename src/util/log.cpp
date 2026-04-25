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

void Logger::log(LogLevel level, std::string_view tag, std::string_view msg)
{
	if (!tag.empty(0))

	if (level >= m_level)
	{
		std::println("{}{} {:<10}  {}\e[0m"
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
	case LogLevel::FATAL:   return "\e[0;101m";
	case LogLevel::ERROR:   return "\e[0;101m";
	case LogLevel::WARNING: return "\e[0;103m";
	case LogLevel::INFO:    return "\e[0;107m";
	case LogLevel::DEBUG:   return "\e[0;105m";
	case LogLevel::TRACE:   return "\e[0;106m";
	default:				return "\e[0m";
	}
}