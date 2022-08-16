#include "log.hpp"
#include "log_c.h"

#include "HAL/hal_namespace.h"

#include "FAL/fal_namespace.h"

#include "MAL/mal_namespace.h"

#include "PAL/pal_namespace.h"

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
