// SPDX-License-Identifier: CC0-1.0
/**
 * @file nkfdtlib.h
 *
 */
#ifndef NKFDTLIB_H_
#define NKFDTLIB_H_

#ifdef __cplusplus
#include <cstddef>
#include <cstdint>
using std::uintptr_t;
using std::uint32_t;
using std::uint8_t;
#else
#include <stddef.h>
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef int      nkfdt_error;
typedef uint32_t nkfdt_tag;

struct fdt_header;

nkfdt_error nkfdt_parse_header(const void* fdt, size_t *nextoffset, struct fdt_header* h);

void* nkfdt_skip_node(const void* fdt, size_t* nextoffset, const struct fdt_header* h);
void* nkfdt_skip_prop(const void* fdt, size_t* nextoffset, const struct fdt_header* h);
char* nkfdt_get_string(const void* fdt, size_t offset, size_t* strlenp, struct fdt_header* h);

nkfdt_error nkfdt_get_prop_data(const void* fdt, size_t offset, void* buf, size_t* lenp);
nkfdt_error nkfdt_set_prop_data(const void* fdt, size_t offset, const void* buf, size_t len);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* NKFDTLIB_H_ */
