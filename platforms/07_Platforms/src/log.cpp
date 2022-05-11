#include "log.hpp"
#include "log_c.h"

#include <cstdarg>
#include <cstdint>

#include <stdio.h>

namespace bm {
namespace log {

namespace log_in {

void OutputLogBase::outputV(LogLevel level, const char* fmt, std::va_list varg)
{
    vprintf(fmt, varg);
    printf("\n");
}

void output_logV(LogLevel level, const char* fmt, std::va_list varg)
{
    OutputLogBase::outputV(level, fmt, varg);
}

} // namespace log_in

using log_in::output_logV;

void fatal(const char* fmt, ...)
{
    std::va_list varg;
    va_start(varg, fmt);
    output_logV(log_in::FATAL, fmt, varg);
    va_end(varg);
}

void error(const char* fmt, ...)
{
    std::va_list varg;
    va_start(varg, fmt);
    output_logV(log_in::ERROR, fmt, varg);
    va_end(varg);
}

void warn(const char* fmt, ...)
{
    std::va_list varg;
    va_start(varg, fmt);
    output_logV(log_in::WARN, fmt, varg);
    va_end(varg);
}

void notice(const char* fmt, ...)
{
    std::va_list varg;
    va_start(varg, fmt);
    output_logV(log_in::NOTICE, fmt, varg);
    va_end(varg);
}

void info(const char* fmt, ...)
{
    std::va_list varg;
    va_start(varg, fmt);
    output_logV(log_in::INFO, fmt, varg);
    va_end(varg);
}

void debug(const char* fmt, ...)
{
    std::va_list varg;
    va_start(varg, fmt);
    output_logV(log_in::DEBUG, fmt, varg);
    va_end(varg);
}

void trace(const char* fmt, ...)
{
    std::va_list varg;
    va_start(varg, fmt);
    output_logV(log_in::TRACE, fmt, varg);
    va_end(varg);
}

} // namespace log
} // namespace bm

extern "C" {

void bm_log_outputV(int level, const char* fmt, va_list varg)
{
    using namespace bm::log::log_in;
    const LogLevel t[BM_LOG_LEVEL_ALL] = {
        ALL, FATAL, ERROR, WARN, NOTICE, INFO, DEBUG, TRACE
    };

    if ((level >= 0) || (level < BM_LOG_LEVEL_ALL)) {
        output_logV(t[level], fmt, varg);
    }
}

void bm_fatal(const char* fmt, ...)
{
    va_list varg;
    va_start(varg, fmt);
    bm::log::log_in::output_logV(bm::log::log_in::FATAL, fmt, varg);
    va_end(varg);
}

void bm_error(const char* fmt, ...)
{
    va_list varg;
    va_start(varg, fmt);
    bm::log::log_in::output_logV(bm::log::log_in::ERROR, fmt, varg);
    va_end(varg);
}

void bm_warn(const char* fmt, ...)
{
    va_list varg;
    va_start(varg, fmt);
    bm::log::log_in::output_logV(bm::log::log_in::WARN, fmt, varg);
    va_end(varg);
}

void bm_notice(const char* fmt, ...)
{
    va_list varg;
    va_start(varg, fmt);
    bm::log::log_in::output_logV(bm::log::log_in::NOTICE, fmt, varg);
    va_end(varg);
}

void bm_info(const char* fmt, ...)
{
    va_list varg;
    va_start(varg, fmt);
    bm::log::log_in::output_logV(bm::log::log_in::INFO, fmt, varg);
    va_end(varg);
}

void bm_debug(const char* fmt, ...)
{
    va_list varg;
    va_start(varg, fmt);
    bm::log::log_in::output_logV(bm::log::log_in::DEBUG, fmt, varg);
    va_end(varg);
}

void bm_trace(const char* fmt, ...)
{
    va_list varg;
    va_start(varg, fmt);
    bm::log::log_in::output_logV(bm::log::log_in::TRACE, fmt, varg);
    va_end(varg);
}

} // extern "C"
