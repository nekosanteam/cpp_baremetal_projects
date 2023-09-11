/* SPDX-License-Identifier: MIT-0 */
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
