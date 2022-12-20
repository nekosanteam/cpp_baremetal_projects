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

nkfdt_error nkfdt_check_header(const void* fdt);
nkfdt_tag   nkfdt_next_tag(const void* fdt, uint32_t startoffset, uint32_t* nextoffset);
nkfdt_error nkfdt_next_node(const void* fdt, uint32_t startoffset, uint32_t* nextoffset);
nkfdt_error nkfdt_get_property(const void* fdt, uint32_t offset, char** name, int* lenp);
nkfdt_error nkfdt_set_property(const void* fdt, uint32_t offset, const char* name, const void* val, int len);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* NKFDTLIB_H_ */
