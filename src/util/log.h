#pragma once
#include <print>
#include <string>

namespace logger {

	constexpr std::string_view WHITE  = "\033[37m";
	constexpr std::string_view RED	  = "\e[0;31m";
	constexpr std::string_view YELLOW = "\e[0;33m";
	constexpr std::string_view BLUE	  = "\e[0;34m";
	constexpr std::string_view CYAN   = "\e[0;36m";

	enum class Level
	{
		Debug,
		Trace,
		Info,
		Warning,
		Error,
		Fatal
	};

	template <typename... Args>
	inline void log(const Level level, std::string_view tag, Args... args)
	{
#ifdef _DEBUG
		std::string_view color;
		std::string_view prefix;
		switch (level)
		{
			case Level::Debug:
				color = BLUE;	prefix = "DEBUG"; break;
			case Level::Trace:
				color = CYAN;	prefix = "TRACE"; break;
			case Level::Info:
				color = WHITE;	prefix = "INFO";  break;
			case Level::Warning:
				color = YELLOW;	prefix = "WARN";  break;
			case Level::Error:
				color = RED;	prefix = "ERROR"; break;
			case Level::Fatal:
				color = RED;	prefix = "FATAL"; break;
		}

		std::print("{}[{}][{}]\t", color, prefix, tag);
		std::println(args...);
#endif
		if (level == Level::Fatal) std::abort();
	}

	template <typename... Args>
	inline void debug(std::string_view tag, Args... args)
	{
		log(Level::Debug, tag, args...);
	}

	template <typename... Args>
	inline void trace(std::string_view tag, Args... args)
	{
		log(Level::Trace, tag, args...);
	}

	template <typename... Args>
	inline void info(std::string_view tag, Args... args)
	{
		log(Level::Info, tag, args...);
	}

	template <typename... Args>
	inline void warning(std::string_view tag, Args... args)
	{
		log(Level::Warning, tag, args...);
	}

	template <typename... Args>
	inline void error(std::string_view tag, Args... args)
	{
		log(Level::Error, tag, args...);
	}

	template <typename... Args>
	inline void fatal(std::string_view tag, Args... args)
	{
		log(Level::Fatal, tag, args...);
	}

}