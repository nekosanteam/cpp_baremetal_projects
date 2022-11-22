// SPDX-License-Identifier: CC0-1.0
#ifndef NKSTRING_CONFIG_H_
#define NKSTRING_CONFIG_H_

#define SUPPORT_UTF8  1
#define SUPPORT_UTF16 1
#define SUPPORT_UTF32 1

#define SUPPORT_SURROGATE_PAIR 1

#ifndef NK_CONFIG_RSIZE_MAX
#ifdef NK_RSIZE_MAX
#define NK_CONFIG_RSIZE_MAX NK_RSIZE_MAX
#else
#define NK_CONFIG_RSIZE_MAX RSIZE_MAX
#endif
#endif

#endif
