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

#ifndef NK_SELFCHECKS_MAIN_H_
#define NK_SELFCHECKS_MAIN_H_
/**
 * @file selfchecks_main.h
 */

#ifdef __cplusplus
#include <cstdint>
using pr_timespec = std::uint64_t;
#else
#include <stdint.h>
typedef uint64_t pr_timespec;
#endif

#ifdef __cplusplus
namespace nk {
namespace work {

} // namespace work
} // namespace nk
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

#define MAIN_SUCCESS (0)
#define MAIN_FAILURE (1)

#define E_OK (0)

struct selfchecks_option;

struct selfchecks_option* selfchecks_parse_args(int argc, char** argv);

void selfchecks_free_option(struct selfchecks_option* opt);

int selfchecks_main(struct selfchecks_option* opt, pr_timespec time[]);

pr_timespec pr_getnowtime();

#ifdef __cplusplus
} // extern "C"
#endif

#endif // NK_SELFCHECKS_MAIN_H_
