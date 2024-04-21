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

#include "HAL/hal_namespace.h"

NAMESPACE_HAL_BEGIN
int gHAL;
NAMESPACE_HAL_END

#include "FAL/fal_namespace.h"

NAMESPACE_FAL_BEGIN
int gFAL;
NAMESPACE_FAL_END

#include "MAL/mal_namespace.h"

NAMESPACE_MAL_BEGIN
int gMAL;
NAMESPACE_MAL_END

#include "PAL/pal_namespace.h"

NAMESPACE_PAL_BEGIN
int gPAL;
NAMESPACE_PAL_END

void test_log_cpp()
{
	using bm::log::debug;
	using bm::log::error;
	using bm::log::fatal;
	using bm::log::info;
	using bm::log::notice;
	using bm::log::trace;
	using bm::log::warn;

	fatal("fatal  %d", 1);
	error("error  %d", 2);
	warn("warn   %d", 3);
	notice("notice %d", 4);
	info("info   %d", 5);
	debug("debug  %d", 6);
	trace("trace  %d", 7);
}

void test_log_c()
{
	bm_fatal("fatal_c  %d", 1);
	bm_error("error_c  %d", 2);
	bm_warn("warn_c   %d", 3);
	bm_notice("notice_c %d", 4);
	bm_info("info_c   %d", 5);
	bm_debug("debug_c  %d", 6);
	bm_trace("trace_c  %d", 7);
}

int main(void)
{
	test_log_cpp();
	test_log_c();

	return 0;
}
