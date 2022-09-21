/**
 * @file nkstring.cpp
 * 
 */
#include "nkstring.h"

#include <array>
#include <cstdint>
#include <utility>

// restrict keyword (C11)
#ifdef __cplusplus
#define nk_restrict
#else
#define nk_restrict restrict
#endif

namespace {

using std::pair;
using std::make_pair;

template <typename AccType>
static inline AccType* nki_strcpy(AccType* nk_restrict dst, const AccType* nk_restrict src)
{
	if (dst == NULL) {
		return NULL;
	}
	if (src == NULL) {
		*dst = (AccType)'\0';
		return dst;
	}

	for (AccType* ptr = dst; *ptr = *src, *src != (AccType)'\0'; ptr++, src++) {
	}

	return dst;
}

template <typename AccType>
static inline AccType* nki_strncpy(AccType* nk_restrict dst, const AccType* nk_restrict src, size_t count)
{
	AccType* ptr = dst;
	size_t   i   = 0;

	if (dst == NULL) {
		return NULL;
	}

	if (src != NULL) {
		while (i < count) {
			*ptr = *src;
			if (*src == (AccType)'\0') {
				break;
			}
			ptr++;
			src++;
			i++;
		}
	}
	while (i < count) {
		*ptr = (AccType)'\0';
		ptr++;
		i++;
	}

	return dst;
}

template <typename AccType>
static inline size_t nki_strlen(const AccType* str)
{
	size_t count;

	if (str == NULL) {
		return 0;
	}
	for (count = 0; *str != (AccType)'\0'; count++, str++)
		;
	return count;
}

template <typename AccType>
static inline size_t nki_strlen_s(const AccType* str, size_t strsz)
{
	size_t count;

	if (str == NULL) {
		return 0;
	}
	for (count = 0; *str != (AccType)'\0'; count++, str++) {
		if (count == strsz) {
			count = 0;
			break;
		}
	}

	return count;
}

template <typename AccType>
static inline AccType* nki_strcat(AccType* nk_restrict dst, const AccType* nk_restrict src)
{
	size_t pos = nki_strlen<AccType>(dst);
	(void)nki_strcpy<AccType>((dst + pos), src);
	return dst;
}

template <typename AccType>
static inline AccType* nki_strncat(AccType* nk_restrict dst, const AccType* nk_restrict src, size_t count)
{
	size_t pos = nki_strlen<AccType>(dst);
	(void)nki_strncpy<AccType>((dst + pos), src, count);
	*(dst + pos + count) = '\0';
	return dst;
}

template <typename AccType>
static inline int nki_strcmp(const AccType* lhs, const AccType* rhs)
{

	while (*lhs == *rhs) {
		if (*lhs == (AccType)'\0') {
			return 0;
		}
		lhs++;
		rhs++;
	}
	if (*lhs < *rhs) {
		return -1;
	} else {
		return 1;
	}
}

template <char>
static inline int nki_strcmp(const char* lhs, const char* rhs)
{
	return nki_strcmp<unsigned char>(
	    reinterpret_cast<const unsigned char*>(lhs), reinterpret_cast<const unsigned char*>(rhs));
}

template <typename AccType>
static inline int nki_strncmp(const AccType* lhs, const AccType* rhs, size_t count)
{
	size_t pos = 0;

	while ((pos < count) && (*lhs == *rhs)) {
		if (*lhs == (AccType)'\0') {
			return 0;
		}
		lhs++;
		rhs++;
		pos++;
	}
	if (pos >= count) {
		return 0;
	}
	if (*lhs < *rhs) {
		return -1;
	} else {
		return 1;
	}
}

template <char>
static inline int nki_strncmp(const char* lhs, const char* rhs, size_t count)
{
	return nki_strncmp<unsigned char>(
	    reinterpret_cast<const unsigned char*>(lhs), reinterpret_cast<const unsigned char*>(rhs), count);
}

template <typename AccType>
static inline AccType* nki_strchr(const AccType* str, AccType ch)
{
	const AccType* pos = str;

	for (; (*pos != ch) && (*pos != (AccType)'\0'); pos++) {
	}
	if (*pos == ch) {
		return const_cast<AccType*>(pos);
	} else {
		return NULL;
	}
}

template <typename AccType>
static inline AccType* nki_strrchr(const AccType* str, AccType ch)
{
	const AccType* pos = str + nki_strlen(str);

	for (; (*pos != ch) && (pos != str); pos--) {
	}
	if (*pos == ch) {
		return const_cast<AccType*>(pos);
	} else {
		return NULL;
	}
}

static inline void* nki_memchr(const void* ptr, int ch, size_t count)
{
	const unsigned char* pos = static_cast<const unsigned char*>(ptr);

	for (size_t i = 0; i < count; i++) {
		if (*pos == static_cast<unsigned char>(ch)) {
			return const_cast<void*>(static_cast<const void*>(pos));
		}
        pos++;
	}
	return NULL;
}

static inline int nki_memcmp(const void* lhs, const void* rhs, size_t count)
{
	const unsigned char* lhs_u = static_cast<const unsigned char*>(lhs);
	const unsigned char* rhs_u = static_cast<const unsigned char*>(rhs);

	for (size_t i = 0; i < count; i++) {
		if (*lhs_u < *rhs_u) {
			return -1;
		} else if (*lhs_u > *rhs_u) {
			return 1;
		}
        lhs_u++;
        rhs_u++;
	}
	return 0;
}

static inline void* nki_memset(void* dst, int ch, size_t count)
{
	unsigned char* pos = static_cast<unsigned char*>(dst);

	for (size_t i = 0; i < count; i++, pos++) {
		*pos = static_cast<unsigned char>(ch);
	}

	return dst;
}

static inline void* nki_memcpy(void* nk_restrict dst, const void* nk_restrict src, size_t count)
{
	unsigned char*       dst_u = static_cast<unsigned char*>(dst);
	const unsigned char* src_u = static_cast<const unsigned char*>(src);

	for (size_t i = 0; i < count; i++) {
		*dst_u = *src_u;
		dst_u++;
		src_u++;
	}

	return dst;
}

static inline void* nki_memmove(void* dst, const void* src, size_t count)
{

	if ((src <= dst) && (dst < (static_cast<const unsigned char*>(src) + count))) {
		unsigned char*       dst_u = static_cast<unsigned char*>(dst);
		const unsigned char* src_u = static_cast<const unsigned char*>(src);
		dst_u += count;
		src_u += count;
		for (size_t i = count; dst_u >= dst; i++) {
			dst_u--;
			src_u--;
			*dst_u = *src_u;
		}
		return dst;
	} else {
		return nki_memcpy(dst, src, count);
	}
}

typedef uint32_t nki_mbstate;
typedef uint8_t  nki_char8;
typedef uint16_t nki_char16;
typedef uint32_t nki_char32;

static inline nki_mbstate nki_mbstate_clear()
{
	return 0;
}

static inline bool nki_mbstate_initial(nki_mbstate v)
{
	return (v == 0);
}

static inline nki_mbstate nki_mbstate_shift(nki_mbstate v, int shift)
{
	return ((v) << (shift));
}

static inline nki_mbstate nki_mbstate_unshift(nki_mbstate v, int shift)
{
	return ((v) >> (shift));
}

static inline nki_mbstate nki_mbstate_put_rest(nki_mbstate v, size_t r)
{
	return (((v) & ~0x0Fu) | static_cast<nki_mbstate>(r & 0x0Fu));
}

static inline size_t nki_mbstate_get_rest(nki_mbstate v)
{
	return static_cast<size_t>(v & 0x0Fu);
}

static inline nki_mbstate nki_mbstate_putc8(nki_mbstate v, nki_char8 c, nki_char8 mask)
{
	return (((v) & ~static_cast<nki_mbstate>(mask)) | static_cast<nki_mbstate>((c) & (mask)));
}

static inline nki_mbstate nki_mbstate_putc16(nki_mbstate v, nki_char16 c, nki_char16 mask)
{
	return (((v) & ~static_cast<nki_mbstate>(mask)) | static_cast<nki_mbstate>((c) & (mask)));
}

static inline nki_char8 nki_mbstate_getc8(nki_mbstate v)
{
	return static_cast<nki_char8>(v & 0xFFu);
}

static inline nki_char16 nki_mbstate_getc16(nki_mbstate v)
{
	return static_cast<nki_char16>(v & 0xFFFFu);
}

static inline nki_char32 nki_mbstate_getc32(nki_mbstate v)
{
	return static_cast<nk_char32>(v);
}

struct c8rconv {
    const nk_char8* c8s;
    size_t rest;
    nk_mbstate st;
};

typedef uint32_t nki_char16pair;

static inline nki_char16pair nki_c32toc16(nki_char32 c32)
{
	if (c32 > 0xFFFFu) {
		nki_char16 c0 = static_cast<nki_char16>((c32 >> 16) & 0x1F);
		c0 = c0 - 1;
		c0 = (c0 << 6) | 0xD800u;
		nki_char16pair result = (static_cast<nki_char16pair>(c0) << 16) | 0xDC00;
		result = result | static_cast<nki_char16pair>(c32 & 0x3FFu); 
		return result;
	}
	else {
		return static_cast<nki_char16pair>(c32 & 0xFFFFu);
	}
}

static inline pair<nki_char32, c8rconv> nki_c8rtoc32(const nk_char8* c8s, size_t n, nk_mbstate st)
{
	if (nki_mbstate_initial(st)) {
		nki_char8 c0 = *c8s;
		c8s++;
		n--;

		if ((c0 & 0x80u) == 0) {
			return make_pair((nki_char32)(c0), c8rconv{ .c8s = c8s, .rest = n, .st = nki_mbstate_clear() });
		}

		if ((c0 & 0xE0u) == 0xC0u) {
			st = nki_mbstate_putc8(st, c0, 0x1Fu);
			st = nki_mbstate_shift(st, 6);
			st = nki_mbstate_put_rest(st, 1);
		}
		else if ((c0 & 0xF0u) == 0xE0u) {
			st = nki_mbstate_putc8(st, c0, 0x0Fu);
			st = nki_mbstate_shift(st, 6);
			st = nki_mbstate_put_rest(st, 2);
        }
		else if ((c0 & 0xF8u) == 0xF0u) {
			st = nki_mbstate_putc8(st, c0, 0x07u);
			st = nki_mbstate_shift(st, 6);
			st = nki_mbstate_put_rest(st, 3);
        }
		else {
			return make_pair(0, c8rconv{ .c8s = c8s, .rest = n, .st = nki_mbstate_clear() });
		}
	}

	size_t rest = nki_mbstate_get_rest(st);
	st = nki_mbstate_unshift(st, 6);
	while ((rest>0) && (n>0)) {
		nk_char8 c1 = *c8s;
		c8s++;
		n--;

		if ((c1 & 0xC0u) != 0x80u) {
			return make_pair(0, c8rconv{ .c8s = c8s, .rest = n, .st = nki_mbstate_clear() });
		}
		st = nki_mbstate_shift(st, 6);
		st = nki_mbstate_putc8(st, c1, 0x3F);
		rest--;
	}

	if (rest==0) {
		nk_char32 c32 = nki_mbstate_getc32(st);
		return make_pair(c32, c8rconv{ .c8s = c8s, .rest = n, .st = nki_mbstate_clear() });
	}

	// rest!=0 && n==0
	st = nki_mbstate_shift(st, 6);
	st = nki_mbstate_put_rest(st, rest);
	return make_pair(0, c8rconv{ .c8s = c8s, .rest = n, .st = st });
}

static inline pair<nki_char16pair, c8rconv> nki_c8rtoc16(const nk_char8* c8s, size_t n, nk_mbstate st)
{
	auto result = nki_c8rtoc32(c8s, n, st);
	return make_pair(nki_c32toc16(result.first), result.second);
}

} // namespace

nk_char* nk_strcpy(nk_char* nk_restrict dst, const nk_char* nk_restrict src)
{
	return nki_strcpy<nk_char>(dst, src);
}

nk_char* nk_strncpy(nk_char* nk_restrict dst, const nk_char* nk_restrict src, size_t count)
{
	return nki_strncpy<nk_char>(dst, src, count);
}

nk_char* nk_strcat(nk_char* nk_restrict dst, const nk_char* nk_restrict src)
{
	return nki_strcat<nk_char>(dst, src);
}

nk_char* nk_strncat(nk_char* nk_restrict dst, const nk_char* nk_restrict src, size_t count)
{
	return nki_strncat<nk_char>(dst, src, count);
}

size_t nk_strxfrm(nk_char* nk_restrict dst, const nk_char* nk_restrict src, size_t count);

size_t nk_strlen(const nk_char* str)
{
	return nki_strlen<nk_char>(str);
}

size_t nk_strlen_s(const nk_char* str, size_t strsz)
{
	return nki_strlen_s<nk_char>(str, strsz);
}

int nk_strcmp(const nk_char* lhs, const nk_char* rhs)
{
	return nki_strcmp<nk_char>(lhs, rhs);
}

int nk_strncmp(const nk_char* lhs, const nk_char* rhs, size_t count)
{
	return nki_strncmp<nk_char>(lhs, rhs, count);
}

nk_char* nk_strchr(const nk_char* str, int ch)
{
	return nki_strchr<nk_char>(str, (nk_char)ch);
}

nk_char* nk_strrchr(const nk_char* str, int ch)
{
	return nki_strrchr<nk_char>(str, (nk_char)ch);
}

void* nk_memchr(const void* ptr, int ch, size_t count)
{
	return nki_memchr(ptr, ch, count);
}

int nk_memcmp(const void* lhs, const void* rhs, size_t count)
{
	return nki_memcmp(lhs, rhs, count);
}

void* nk_memset(void* dst, int ch, size_t count)
{
	return nki_memset(dst, ch, count);
}

void* nk_memcpy(void* nk_restrict dst, const void* nk_restrict src, size_t count)
{
	return nki_memcpy(dst, src, count);
}

void* nk_memmove(void* dst, const void* src, size_t count)
{
	return nki_memmove(dst, src, count);
}

#undef nk_restrict
