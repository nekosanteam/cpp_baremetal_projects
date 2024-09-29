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

#include "nklogger.h"
#include <cstddef>
#include <cstdint>
#include <cstdarg>

#include <cstdio>

using std::va_list;

#define WEAK_SYMBOL __attribute__((weak))

using std::vfprintf;

void nkpr_emerg(const char* fmt, va_list varg) WEAK_SYMBOL;
void nkpr_alert(const char* fmt, va_list varg) WEAK_SYMBOL;
void nkpr_fatal(const char* fmt, va_list varg) WEAK_SYMBOL;
void nkpr_emerg(const char* fmt, va_list varg) WEAK_SYMBOL;
void nkpr_error(const char* fmt, va_list varg) WEAK_SYMBOL;
void nkpr_warn(const char* fmt, va_list varg) WEAK_SYMBOL;
void nkpr_notice(const char* fmt, va_list varg) WEAK_SYMBOL;
void nkpr_info(const char* fmt, va_list varg) WEAK_SYMBOL;
void nkpr_debug(const char* fmt, va_list varg) WEAK_SYMBOL;
void nkpr_trace(const char* fmt, va_list varg) WEAK_SYMBOL;

void nkpr_emerg(const char* fmt, va_list varg)
{
	vfprintf(stderr, fmt, varg);
}

void nkpr_alert(const char* fmt, va_list varg)
{
	vfprintf(stderr, fmt, varg);
}

void nkpr_fatal(const char* fmt, va_list varg)
{
	vfprintf(stderr, fmt, varg);
}

void nkpr_error(const char* fmt, va_list varg)
{
	vfprintf(stderr, fmt, varg);
}

void nkpr_warn(const char* fmt, va_list varg)
{
	vfprintf(stderr, fmt, varg);
}

void nkpr_notice(const char* fmt, va_list varg)
{
	vfprintf(stdout, fmt, varg);
}

void nkpr_info(const char* fmt, va_list varg)
{
	vfprintf(stdout, fmt, varg);
}

void nkpr_debug(const char* fmt, va_list varg)
{
	vfprintf(stdout, fmt, varg);
}

void nkpr_trace(const char* fmt, va_list varg)
{
	vfprintf(stdout, fmt, varg);
}

void nk_emerg(const char* fmt, ...)
{
	va_list varg;

	va_start(varg, fmt);
	nkpr_emerg(fmt, varg);
	va_end(varg);
}

void nk_alert(const char* fmt, ...)
{
	va_list varg;

	va_start(varg, fmt);
	nkpr_alert(fmt, varg);
	va_end(varg);
}

void nk_fatal(const char* fmt, ...)
{
	va_list varg;

	va_start(varg, fmt);
	nkpr_fatal(fmt, varg);
	va_end(varg);
}

void nk_error(const char* fmt, ...)
{
	va_list varg;

	va_start(varg, fmt);
	nkpr_error(fmt, varg);
	va_end(varg);
}

void nk_warn(const char* fmt, ...)
{
	va_list varg;

	va_start(varg, fmt);
	nkpr_warn(fmt, varg);
	va_end(varg);
}

void nk_notice(const char* fmt, ...)
{
	va_list varg;

	va_start(varg, fmt);
	nkpr_notice(fmt, varg);
	va_end(varg);
}

void nk_info(const char* fmt, ...)
{
	va_list varg;

	va_start(varg, fmt);
	nkpr_info(fmt, varg);
	va_end(varg);
}

void nk_debug(const char* fmt, ...)
{
	va_list varg;

	va_start(varg, fmt);
	nkpr_debug(fmt, varg);
	va_end(varg);
}

void nk_trace(const char* fmt, ...)
{
	va_list varg;

	va_start(varg, fmt);
	nkpr_trace(fmt, varg);
	va_end(varg);
}

