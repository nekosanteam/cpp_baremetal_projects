// SPDX-License-Identifier: CC0-1.0
/**
 * @file cyclictest_main.h
 */
#ifndef NK_CYCLICTEST_MAIN_H_
#define NK_CYCLICTEST_MAIN_H_

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

struct cyclictest_option;

struct cyclictest_option* cyclictest_parse_args(int argc, char** argv);

void cyclictest_free_option(struct cyclictest_option* opt);

int cyclictest_main(struct cyclictest_option* opt);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // NK_CYCLICTEST_MAIN_H_
