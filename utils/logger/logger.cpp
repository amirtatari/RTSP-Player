#include "logger.hpp"
#include <iostream>
#include <chrono>
#include <iomanip>

Logger& Logger::instance() 
{
    static Logger instance;
    return instance;
}

void Logger::log(LogLevel level, std::string_view message) 
{
    std::lock_guard<std::mutex> lock(m_mutex);

    const auto now {std::chrono::system_clock::now()};
    const auto time {std::chrono::system_clock::to_time_t(now)};
    const auto ms {std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000};

    std::ostream& out = (level == LogLevel::ERROR) ? std::cerr : std::cout;

    out << "[" << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S")
        << "." << std::setfill('0') << std::setw(3) << ms.count() << "] ";

    switch (level) 
    {
        case LogLevel::DEBUG:   out << "[DEBUG] "; break;
        case LogLevel::INFO:    out << "[INFO] "; break;
        case LogLevel::WARNING: out << "[WARNING] "; break;
        case LogLevel::ERROR:   out << "[ERROR] "; break;
    }

    out << message << '\n';
}
