#include "log.hpp"
#include "log_c.h"

#include <cstdarg>
#include <cstdint>

#include <stdio.h>

namespace bm {
namespace log {

namespace in_log {

void OutputLogBase::outputV(LogLevel level, const char* fmt, std::va_list varg)
{
	vprintf(fmt, varg);
	printf("\n");
}

void output_logV(LogLevel level, const char* fmt, std::va_list varg)
{
	OutputLogBase::outputV(level, fmt, varg);
}

} // namespace in_log

using in_log::output_logV;

void fatal(const char* fmt, ...)
{
	std::va_list varg;
	va_start(varg, fmt);
	output_logV(in_log::FATAL, fmt, varg);
	va_end(varg);
}

void error(const char* fmt, ...)
{
	std::va_list varg;
	va_start(varg, fmt);
	output_logV(in_log::ERROR, fmt, varg);
	va_end(varg);
}

void warn(const char* fmt, ...)
{
	std::va_list varg;
	va_start(varg, fmt);
	output_logV(in_log::WARN, fmt, varg);
	va_end(varg);
}

void notice(const char* fmt, ...)
{
	std::va_list varg;
	va_start(varg, fmt);
	output_logV(in_log::NOTICE, fmt, varg);
	va_end(varg);
}

void info(const char* fmt, ...)
{
	std::va_list varg;
	va_start(varg, fmt);
	output_logV(in_log::INFO, fmt, varg);
	va_end(varg);
}

void debug(const char* fmt, ...)
{
	std::va_list varg;
	va_start(varg, fmt);
	output_logV(in_log::DEBUG, fmt, varg);
	va_end(varg);
}

void trace(const char* fmt, ...)
{
	std::va_list varg;
	va_start(varg, fmt);
	output_logV(in_log::TRACE, fmt, varg);
	va_end(varg);
}

} // namespace log
} // namespace bm

extern "C" {

void bm_log_outputV(int level, const char* fmt, va_list varg)
{
	using namespace bm::log::in_log;
	const LogLevel t[BM_LOG_LEVEL_END] = { NONE, FATAL, ERROR, WARN, NOTICE, INFO, DEBUG, TRACE, ALL };

	if ((level >= 0) || (level < BM_LOG_LEVEL_END)) {
		output_logV(t[level], fmt, varg);
	}
}

void bm_fatal(const char* fmt, ...)
{
	std::va_list varg;
	va_start(varg, fmt);
	bm::log::in_log::output_logV(bm::log::in_log::FATAL, fmt, varg);
	va_end(varg);
}

void bm_error(const char* fmt, ...)
{
	std::va_list varg;
	va_start(varg, fmt);
	bm::log::in_log::output_logV(bm::log::in_log::ERROR, fmt, varg);
	va_end(varg);
}

void bm_warn(const char* fmt, ...)
{
	std::va_list varg;
	va_start(varg, fmt);
	bm::log::in_log::output_logV(bm::log::in_log::WARN, fmt, varg);
	va_end(varg);
}

void bm_notice(const char* fmt, ...)
{
	std::va_list varg;
	va_start(varg, fmt);
	bm::log::in_log::output_logV(bm::log::in_log::NOTICE, fmt, varg);
	va_end(varg);
}

void bm_info(const char* fmt, ...)
{
	std::va_list varg;
	va_start(varg, fmt);
	bm::log::in_log::output_logV(bm::log::in_log::INFO, fmt, varg);
	va_end(varg);
}

void bm_debug(const char* fmt, ...)
{
	std::va_list varg;
	va_start(varg, fmt);
	bm::log::in_log::output_logV(bm::log::in_log::DEBUG, fmt, varg);
	va_end(varg);
}

void bm_trace(const char* fmt, ...)
{
	std::va_list varg;
	va_start(varg, fmt);
	bm::log::in_log::output_logV(bm::log::in_log::TRACE, fmt, varg);
	va_end(varg);
}

} // extern "C"
