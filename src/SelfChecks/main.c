/* SPDX-License-Identifier: MIT-0 */
/**
 * @file main.c
 */

#include "selfchecks_main.h"

#include <stdio.h>

void usage(int argc, char** argv)
{
	char* prog = "selfchecks";
	if (argc > 0) {
		prog = argv[0];
	}

	fprintf(stderr, "%s: \n", prog);
}

int main(int argc, char** argv)
{
	int ret;

	struct selfchecks_option* opt;

	opt = selfchecks_parse_args(argc, argv);
	if (!opt) {
		usage(argc, argv);
		return MAIN_FAILURE;
	}

	ret = selfchecks_main(opt);

	selfchecks_free_option(opt);

	return ret;
}
