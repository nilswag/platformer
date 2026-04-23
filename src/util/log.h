#pragma once

namespace logger {

	enum class LogLevel
	{
		DEBUG,
		TRACE,
		INFO,
		WARNING,
		FATAL
	};

#ifdef _DEBUG
	template <typename... Args>
	inline void log()
	{
		std::cout << "blah";
	}
#else
	template <typename... Args>
	inline void log() { }
#endif

}