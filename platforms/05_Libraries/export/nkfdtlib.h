/* SPDX-License-Identifier: MIT-0 */
/**
 * @file nkfdtlib.h
 */
#ifndef NKFDTLIB_H_
#define NKFDTLIB_H_

#ifdef __cplusplus
#include <cstddef>
#include <cstdint>
using std::uint32_t;
using std::uint8_t;
using std::uintptr_t;
#else
#include <stddef.h>
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef int      nkfdt_error;
typedef uint32_t nkfdt_tag;

enum {
	NKFDT_OK = 0,
	NKFDT_ERROR,
};

#define NKFDT_BEGIN_NODE 0x01
#define NKFDT_END_NODE   0x02
#define NKFDT_PROP       0x03
#define NKFDT_NOP        0x04
#define NKFDT_END        0x09

struct fdt_header;

nkfdt_error nkfdt_parse_header(const void* fdt, size_t* nextoffset, struct fdt_header* h);

void* nkfdt_skip_node(const void* fdt, size_t* nextoffset, const struct fdt_header* h);
void* nkfdt_skip_prop(const void* fdt, size_t* nextoffset, const struct fdt_header* h);
char* nkfdt_get_string(const void* fdt, size_t str_off, int* strlenp, struct fdt_header* h);

nkfdt_error nkfdt_get_prop_data(const void* fdt, size_t offset, void* buf, size_t* lenp);
nkfdt_error nkfdt_set_prop_data(const void* fdt, size_t offset, const void* buf, size_t len);

void* nks_memcpy(void* dst, const void* src, size_t n);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* NKFDTLIB_H_ */
