// SPDX-License-Identifier: CC0-1.0
/**
 * @file main.c
 */

#include "cyclictest_main.h"

int main(int argc, char** argv)
{
	int ret;

	struct cyclictest_option* opt;

	opt = cyclictest_parse_args(argc, argv);

	ret = cyclictest_main(opt);

	return ret;
}
