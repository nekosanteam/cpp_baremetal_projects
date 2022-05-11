#pragma once
/**
 * @file bm/log.hpp
 * @brief
 * 
 */
#include <cstdarg>
#include <cstdint>

namespace bm {
namespace log {

void fatal(const char* fmt, ...);
void error(const char* fmt, ...);
void warn(const char* fmt, ...);
void notice(const char* fmt, ...);
void info(const char* fmt, ...);
void debug(const char* fmt, ...);
void trace(const char* fmt, ...);

namespace log_in {

enum LogLevel {
    NONE,
    FATAL,
    ERROR,
    WARN,
    NOTICE,
    INFO,
    DEBUG,
    TRACE,
    ALL,
};

void output_logV(LogLevel level, const char* fmt, std::va_list varg);

class OutputLogBase {
public:
    static void outputV(LogLevel level, const char* fmt, std::va_list varg);
};

} // namespace log_in

} // namespace log
} // namespace bm
