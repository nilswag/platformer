#pragma once
#include <iostream>
#include <format>
#include <string>

// TODO: add log categories like [BLAH] and stuff.

namespace logger {

	enum class Level
	{
		DEBUG,
		TRACE,
		INFO,
		WARNING,
		ERROR,
		FATAL
	};

	template <typename... Args>
	inline void log(const Level level, const std::format_string<Args...> fmt, Args... args)
	{
#ifdef _DEBUG
		std::string msg = std::vformat(fmt.get(), std::make_format_args(args...));

		switch (level)
		{
		case Level::DEBUG:	 std::cout << "\033[34m" << "[DEBUG]\t" << msg << "\033[0m\n"; break;
		case Level::TRACE:	 std::cout << "\033[36m" << "[TRACE]\t" << msg << "\033[0m\n"; break;
		case Level::INFO:	 std::cout << "\033[37m" << "[INFO]\t" << msg << "\033[0m\n";  break;
		case Level::WARNING: std::cout << "\033[33m" << "[WARN]\t" << msg << "\033[0m\n";  break;
		case Level::ERROR:	 std::cout << "\033[31m" << "[ERROR]\t" << msg << "\033[0m\n"; break;
		case Level::FATAL:
			std::cout << "\033[31m" << "[FATAL]\t" << msg << "\033[0m\n";
			break;
		}	
#endif
		if (level == Level::FATAL) std::abort();
	}

	template <typename... Args>
	inline void debug(const std::format_string<Args...> fmt, Args... args)
	{
		log(Level::DEBUG, fmt, args...);
	}

	template <typename... Args>
	inline void trace(const std::format_string<Args...> fmt, Args... args)
	{
		log(Level::TRACE, fmt, args...);
	}

	template <typename... Args>
	inline void info(const std::format_string<Args...> fmt, Args... args)
	{
		log(Level::INFO, fmt, args...);
	}

	template <typename... Args>
	inline void warning(const std::format_string<Args...> fmt, Args... args)
	{
		log(Level::WARNING, fmt, args...);
	}

	template <typename... Args>
	inline void error(const std::format_string<Args...> fmt, Args... args)
	{
		log(Level::ERROR, fmt, args...);
	}

	template <typename... Args>
	inline void fatal(const std::format_string<Args...> fmt, Args... args)
	{
		log(Level::FATAL, fmt, args...);
	}

}