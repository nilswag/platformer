#pragma once
#include <string_view>
#include <format>

enum class LogLevel
{
	FATAL = 0,
	ERROR,
	WARNING,
	INFO,
	DEBUG,
	TRACE
};

class Logger
{
public:
    Logger(const Logger&) = delete;
    void operator=(const Logger&) = delete;

    Logger(Logger&&) = delete;
    void operator=(Logger&&) = delete;

    template<typename... Args>
    inline void fatal(std::string_view tag, std::format_string<Args...> fmt, Args&&... args)
    {
        log(LogLevel::FATAL, tag, std::format(fmt, std::forward<Args>(args)...));
    }

    template<typename... Args>
    inline void err(std::string_view tag, std::format_string<Args...> fmt, Args&&... args)
    {
        log(LogLevel::ERROR, tag, std::format(fmt, std::forward<Args>(args)...));
    }

    template<typename... Args>
    inline void warn(std::string_view tag, std::format_string<Args...> fmt, Args&&... args)
    {
        log(LogLevel::WARNING, tag, std::format(fmt, std::forward<Args>(args)...));
    }

    template<typename... Args>
    inline void info(std::string_view tag, std::format_string<Args...> fmt, Args&&... args)
    {
        log(LogLevel::INFO, tag, std::format(fmt, std::forward<Args>(args)...));
    }

    template<typename... Args>
    inline void debug(std::string_view tag, std::format_string<Args...> fmt, Args&&... args)
    {
        log(LogLevel::DEBUG, tag, std::format(fmt, std::forward<Args>(args)...));
    }

    template<typename... Args>
    inline void trace(std::string_view tag, std::format_string<Args...> fmt, Args&&... args)
    {
        log(LogLevel::TRACE, tag, std::format(fmt, std::forward<Args>(args)...));
    }

    inline LogLevel getLevel() const { return m_level; }
    inline void setLevel(LogLevel level) { m_level = level; }

    static Logger& getInstance();

private:
    Logger();
    void log(LogLevel level, std::string_view tag, std::string_view msg) const;

    static constexpr std::string_view levelStr(LogLevel level);
    static constexpr std::string_view colorStr(LogLevel level);

    LogLevel m_level;
};

inline Logger& log()
{
    return Logger::getInstance();
}