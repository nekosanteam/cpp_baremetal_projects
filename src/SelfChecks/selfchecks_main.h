/* SPDX-License-Identifier: MIT-0 */
/**
 * @file selfchecks_main.h
 */
#ifndef NK_SELFCHECKS_MAIN_H_
#define NK_SELFCHECKS_MAIN_H_

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
