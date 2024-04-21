/* SPDX-License-Identifier: BSD-1-Clause */
/*
 * Copyright 2023,2024 nekosanteam <1688092+nekosanteam@users.noreply.github.com>. All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions
 *    and the following disclaimer.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS
 * AND CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

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
