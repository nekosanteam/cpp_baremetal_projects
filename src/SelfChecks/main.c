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
/**
 * @file main.c
 */
#define _GNU_SOURCE
#include "selfchecks_main.h"

#include <stdio.h>
#include <time.h>

void usage(int argc, char** argv)
{
	char* prog = "selfchecks";
	if (argc > 0) {
		prog = argv[0];
	}

	fprintf(stderr, "%s: \n", prog);
}

pr_timespec pr_getnowtime()
{
	struct timespec tv;
	pr_timespec     ret;

	clock_gettime(CLOCK_REALTIME, &tv);
	ret = ((pr_timespec)tv.tv_sec * 1000 * 1000 * 1000) + ((pr_timespec)tv.tv_nsec);

	return ret;
}

int main(int argc, char** argv)
{
	int         ret;
	pr_timespec time[4];

	struct selfchecks_option* opt;

	opt = selfchecks_parse_args(argc, argv);
	if (!opt) {
		usage(argc, argv);
		return MAIN_FAILURE;
	}

	ret = selfchecks_main(opt, time);
	if (ret == MAIN_SUCCESS) {
		fprintf(stderr, "time1 = %ld\n", (time[1] - time[0]));
		fprintf(stderr, "time2 = %ld\n", (time[2] - time[1]));
	}

	selfchecks_free_option(opt);

	return ret;
}
