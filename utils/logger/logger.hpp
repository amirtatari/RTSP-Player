#pragma once

#include <string_view>
#include <mutex>

#define logger Logger::instance()


/// log levels for the application
enum class LogLevel {DEBUG, INFO, WARNING, ERROR};

/// singleton logger class
class Logger 
{
public:
    /// get the singleton instance
    static Logger& instance();

    /// log a message
    void log(LogLevel level, std::string_view message);

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;

private:
    Logger() = default;
    ~Logger() = default;

    std::mutex m_mutex;
};
