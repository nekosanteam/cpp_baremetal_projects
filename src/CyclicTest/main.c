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
