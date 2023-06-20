// SPDX-License-Identifier: CC0-1.0
/**
 * @file main.c
 */

#include "cyclictest_main.h"

#include <stdio.h>

void usage(int argc, char** argv)
{
	char* prog = "cyclictest";
	if (argc > 0) {
		prog = argv[0];
	}

	fprintf(stderr, "%s: \n", prog);
}

int main(int argc, char** argv)
{
	int ret;

	struct cyclictest_option* opt;

	opt = cyclictest_parse_args(argc, argv);
	if (!opt) {
		usage(argc, argv);
		return MAIN_FAILURE;
	}

	ret = cyclictest_main(opt);

	cyclictest_free_option(opt);

	return ret;
}
