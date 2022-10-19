/**
 * @file nkstring.cpp
 *
 */
#include "nkstring.h"

#include "nkstring/config.h"

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

template <typename AccType>
static inline nk_size nki_strnlen_si(const AccType* str, nk_size strsz)
{
	nk_size count;

	for (count = 0; *str != (AccType)'\0'; count++) {
		if (count == strsz) {
			break;
		}
        str++;
	}

	return count;
}

template <typename AccType>
static inline nk_size nki_strlen(const AccType* str)
{
	return nki_strnlen_si<AccType>(str, (NK_CONFIG_RSIZE_MAX/(sizeof(AccType))));
}

template <typename AccType>
static inline nk_size nki_strnlen(const AccType* str, nk_size strsz)
{
	return nki_strnlen_si<AccType>(str, strsz);
}

template <typename AccType>
static inline nk_size nki_strnlen_s(const AccType* str, nk_size strsz)
{
    if (str == NULL) {
        return 0;
    }
	return nki_strnlen_si<AccType>(str, strsz);
}

template <typename AccType>
static inline nk_size nki_strcpy_si(AccType* nk_restrict dst, nk_size dstsz, const AccType* nk_restrict src, nk_size srcsz)
{
	AccType* ptr = dst;
	nk_size  i   = 0;

    while ((i < dstsz) && (i < srcsz)) {
        *ptr = *src;
        if (*src == (AccType)'\0') {
            break;
        }
        ptr++;
        src++;
        i++;
    }

	return i;
}

nk_size nk_strcpy_si(AccType* nk_restrict dst, nk_size dstsz, const AccType* nk_restrict src, nk_size srcsz)
{
    return nki_strcpy_si(dst, dstsz, src, srcsz);
}

template <typename AccType>
static inline AccType* nki_strncpy_si(AccType* nk_restrict dst, nk_size dstsz, const AccType* nk_restrict src, nk_size srcsz)
{
	AccType* ptr = dst;
	nk_size  i   = 0;
    nk_size  ret;

    if ((dstsz != 0) && (srcsz == 0)) {
        *ptr = (AccType)'\0';
    }
    if (src != NULL) {
        while ((i < dstsz) && (i < srcsz)) {
            *ptr = *src;
            if (*src == (AccType)'\0') {
                break;
            }
            ptr++;
            src++;
            i++;
        }
    }
    ret = i;

	while (i < dstsz) {
		*ptr = (AccType)'\0';
		ptr++;
		i++;
	}

	return ret;
}

template <typename AccType>
static inline nk_errno nki_strcpy_s(AccType* nk_restrict dst, nk_rsize dstsz, const AccType* nk_restrict src)
{
    if (dst == NULL) {
        return NK_EINVAL;
    }
    if (dstsz == 0) {
        return NK_ERANGE;
    }
    if (src == NULL) {
        dst[0] = (AccType)'\0';
        return NK_EINVAL;
    }
    const nk_size sz = (NK_CONFIG_RSIZE_MAX/sizeof(AccType));
    if (sz < dstsz) {
        dst[0] = (AccType)'\0';
        return NK_ERANGE;
    }
    if (dstsz < nki_strnlen(src, sz)) {
        dst[0] = (AccType)'\0';
        return NK_ERANGE;
    }
    (void)nki_strcpy_si<AccType>(dst, dstsz, src, sz);

    return 0;
}

template <typename AccType>
static inline nk_errno nki_strncpy_s(AccType* nk_restrict dst, nk_rsize dstsz, const AccType* nk_restrict src, nk_rsize srcsz)
{
    if (dst == NULL) {
        return NK_EINVAL;
    }
    if (dstsz == 0) {
        return NK_ERANGE;
    }
    if (src == NULL) {
        dst[0] = (AccType)'\0';
        return NK_EINVAL;
    }
    const nk_size sz = (NK_CONFIG_RSIZE_MAX/sizeof(AccType));
    if (sz < dstsz) {
        dst[0] = (AccType)'\0';
        return NK_ERANGE;
    }
    if (sz < srcsz) {
        dst[0] = (AccType)'\0';
        return NK_ERANGE;
    }
    if (dstsz < nki_strnlen(src, srcsz)) {
        return NK_ERANGE;
    }
    (void)nki_strcpy_si<AccType>(dst, dstsz, src, srcsz);

    return 0;
}

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

    nk_size sz = NK_CONFIG_RSIZE_MAX/(sizeof(AccType));
    (void)nki_strcpy_si<AccType>(dst, sz, src, sz);
    return dst;
}

template <typename AccType>
static inline AccType* nki_strncpy(AccType* nk_restrict dst, const AccType* nk_restrict src, nk_rsize count)
{
	if (dst == NULL) {
		return NULL;
	}
    nk_size sz = NK_CONFIG_RSIZE_MAX/(sizeof(AccType));
    if (count > sz) {
        count = sz;
    }

    (void)nki_strncpy_si<AccType>(dst, count, src, sz);
    return dst;
}

template <typename AccType>
static inline nk_rsize nki_strlcpy(AccType* nk_restrict dst, const AccType* nk_restrict src, nk_rsize count)
{
    nk_rsize ret;

	if (dst == NULL) {
		return NULL;
	}
    nk_size sz = NK_CONFIG_RSIZE_MAX/(sizeof(AccType));
    if (count > sz) {
        count = sz;
    }

    (void)nki_strcpy_si<AccType>(dst, count, src, sz);
    *(dst + (count-1)) = (AccType)'\0';
    ret = nki_strlen(*dst);

    return ret;
}

template <typename AccType>
static inline AccType* nki_strcat(AccType* nk_restrict dst, const AccType* nk_restrict src)
{
	nk_size pos = nki_strlen<AccType>(dst);
	(void)nki_strcpy<AccType>((dst + pos), src);
	return dst;
}

template <typename AccType>
static inline AccType* nki_strcat_si(AccType* nk_restrict dst, nk_rsize dstsz, const AccType* nk_restrict src)
{
	nk_size pos = nki_strlen<AccType>(dst);
	(void)nki_strcpy<AccType>((dst + pos), src);
	return dst;
}

template <typename AccType>
static inline nk_errno nki_strcat_s(AccType* nk_restrict dst, nk_rsize dstsz, const AccType* nk_restrict src)
{
	nk_size pos = nki_strlen<AccType>(dst);
	(void)nki_strcpy<AccType>((dst + pos), src);
	return 0;
}

template <typename AccType>
static inline AccType* nki_strncat(AccType* nk_restrict dst, const AccType* nk_restrict src, nk_size count)
{
	nk_size pos = nki_strlen<AccType>(dst);
	(void)nki_strncpy<AccType>((dst + pos), src, count);
	*(dst + pos + count) = '\0';
	return dst;
}

template <typename AccType>
static inline AccType* nki_strncat_si(AccType* nk_restrict dst, const AccType* nk_restrict src, nk_size count)
{
	nk_size pos = nki_strlen<AccType>(dst);
	(void)nki_strncpy<AccType>((dst + pos), src, count);
	*(dst + pos + count) = '\0';
	return dst;
}

template <typename AccType>
static inline nk_errno nki_strncat_s(AccType* nk_restrict dst, const AccType* nk_restrict src, nk_size count)
{
	nk_size pos = nki_strlen<AccType>(dst);
	(void)nki_strncpy<AccType>((dst + pos), src, count);
	*(dst + pos + count) = '\0';
	return 0;
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
	}
	else {
		return 1;
	}
}

template <char>
static inline int nki_strcmp(const char* lhs, const char* rhs)
{
    using uc = unsigned char;
	return nki_strcmp<uc>(reinterpret_cast<const uc*>(lhs), reinterpret_cast<const uc*>(rhs));
}

template <typename AccType>
static inline int nki_strncmp(const AccType* lhs, const AccType* rhs, nk_size count)
{
	nk_size pos = 0;

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
	}
	else {
		return 1;
	}
}

template <char>
static inline int nki_strncmp(const char* lhs, const char* rhs, nk_size count)
{
    using uc = unsigned char;
	return nki_strncmp<uc>(reinterpret_cast<const uc*>(lhs), reinterpret_cast<const uc*>(rhs), count);
}

template <typename AccType>
static inline AccType* nki_strchr(const AccType* str, AccType ch)
{
	const AccType* pos = str;

	for (; (*pos != ch) && (*pos != (AccType)'\0'); pos++) {
	}
	if (*pos == ch) {
		return const_cast<AccType*>(pos);
	}
	else {
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
	}
	else {
		return NULL;
	}
}

static inline void* nki_memchr(const void* ptr, int ch, nk_size count)
{
	const unsigned char* pos = static_cast<const unsigned char*>(ptr);

	for (nk_size i = 0; i < count; i++) {
		if (*pos == static_cast<unsigned char>(ch)) {
			return const_cast<void*>(static_cast<const void*>(pos));
		}
		pos++;
	}
	return NULL;
}

static inline int nki_memcmp(const void* lhs, const void* rhs, nk_size count)
{
	const unsigned char* lhs_u = static_cast<const unsigned char*>(lhs);
	const unsigned char* rhs_u = static_cast<const unsigned char*>(rhs);

	for (nk_size i = 0; i < count; i++) {
		if (*lhs_u < *rhs_u) {
			return -1;
		}
		else if (*lhs_u > *rhs_u) {
			return 1;
		}
		lhs_u++;
		rhs_u++;
	}
	return 0;
}

static inline void* nki_memset(void* dst, int ch, nk_size count)
{
	unsigned char* pos = static_cast<unsigned char*>(dst);

	for (nk_size i = 0; i < count; i++, pos++) {
		*pos = static_cast<unsigned char>(ch);
	}

	return dst;
}

static inline void* nki_memcpy(void* nk_restrict dst, const void* nk_restrict src, nk_size count)
{
	unsigned char*       dst_u = static_cast<unsigned char*>(dst);
	const unsigned char* src_u = static_cast<const unsigned char*>(src);

	for (nk_size i = 0; i < count; i++) {
		*dst_u = *src_u;
		dst_u++;
		src_u++;
	}

	return dst;
}

static inline void* nki_memmove(void* dst, const void* src, nk_size count)
{

	if ((src <= dst) && (dst < (static_cast<const unsigned char*>(src) + count))) {
		unsigned char*       dst_u = static_cast<unsigned char*>(dst);
		const unsigned char* src_u = static_cast<const unsigned char*>(src);
		dst_u += count;
		src_u += count;
		for (nk_size i = count; dst_u >= dst; i++) {
			dst_u--;
			src_u--;
			*dst_u = *src_u;
		}
		return dst;
	}
	else {
		return nki_memcpy(dst, src, count);
	}
}

using std::make_pair;
using std::pair;

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

static inline nki_mbstate nki_mbstate_put_rest(nki_mbstate v, nk_size r)
{
	return (((v) & ~0x0Fu) | static_cast<nki_mbstate>(r & 0x0Fu));
}

static inline nk_size nki_mbstate_get_rest(nki_mbstate v)
{
	return static_cast<nk_size>(v & 0x0Fu);
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
	return static_cast<nk_char32>(v & 0x1FFFFFu);
}

struct c8rconv {
	const nk_char8* c8s;
	nk_size         rest;
	nk_mbstate      st;
};

typedef uint32_t nki_char16pair;

static inline nki_char16pair nki_c32toc16(nki_char32 c32)
{
	if (c32 > 0xFFFFu) {
		nki_char16 c0;
		nki_char16 c1;

		c0 = static_cast<nki_char16>((c32 >> 16) & 0x1F);
		c0 = (((c0 - 1) & 0x0F) << 6);
		c0 = 0xD800u | c0 | ((c32 >> 10) & 0x003Fu);
		c1 = 0xDC00 | static_cast<nki_char16>(c32 & 0x03FFu);
		return (static_cast<nki_char16pair>(c1) << 16) | (static_cast<nki_char16pair>(c0));
	}
	else {
		return static_cast<nki_char16pair>(c32 & 0xFFFFu);
	}
}

static inline pair<nki_char32, c8rconv> nki_c8rtoc32(const nki_char8* c8s, nk_size n, nki_mbstate st)
{
	if (nki_mbstate_initial(st)) {
		nki_char8 c0 = *c8s;
		c8s++;
		n--;

		if ((c0 & 0x80u) == 0) {
			return make_pair((nki_char32)(c0), c8rconv { c8s, n, nki_mbstate_clear() });
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
			return make_pair(0, c8rconv { c8s, n, nki_mbstate_clear() });
		}
	}

	nk_size rest;

	rest = nki_mbstate_get_rest(st);
	st   = nki_mbstate_unshift(st, 6);
	while ((rest > 0) && (n > 0)) {
		nki_char8 c1 = *c8s;
		c8s++;
		n--;

		if ((c1 & 0xC0u) != 0x80u) {
			return make_pair(0, c8rconv { c8s, n, nki_mbstate_clear() });
		}
		st = nki_mbstate_shift(st, 6);
		st = nki_mbstate_putc8(st, c1, 0x3F);
		rest--;
	}

	if (rest == 0) {
		nki_char32 c32 = nki_mbstate_getc32(st);
		return make_pair(c32, c8rconv { c8s, n, nki_mbstate_clear() });
	}

	// rest!=0 && n==0
	st = nki_mbstate_shift(st, 6);
	st = nki_mbstate_put_rest(st, rest);
	return make_pair(0, c8rconv { c8s, n, st });
}

static inline pair<nki_char16pair, c8rconv> nki_c8rtoc16(const nki_char8* c8s, nk_size n, nki_mbstate st)
{
	auto result = nki_c8rtoc32(c8s, n, st);
	return make_pair(nki_c32toc16(result.first), result.second);
}

} // namespace

// char(nk_char)
nk_char* nk_strcpy(nk_char* nk_restrict dst, const nk_char* nk_restrict src)
{
	return nki_strcpy<nk_char>(dst, src);
}

nk_errno nk_strcpy_s(nk_char* nk_restrict dst, nk_rsize dstsz, const nk_char* nk_restrict src)
{
	return nki_strcpy_s<nk_char>(dst, dstsz, src);
}

nk_char* nk_strncpy(nk_char* nk_restrict dst, const nk_char* nk_restrict src, nk_size count)
{
	return nki_strncpy<nk_char>(dst, src, count);
}

nk_errno nk_strncpy_s(nk_char* nk_restrict dst, nk_rsize dstsz, const nk_char* nk_restrict src, nk_size count)
{
	return nki_strncpy_s<nk_char>(dst, dstsz, src, count);
}

nk_size  nk_strlcpy(nk_char* nk_restrict dst, const nk_char* nk_restrict src, nk_size count)
{
	return nki_strlcpy<nk_char>(dst, src, count);
}

nk_char* nk_strcat(nk_char* nk_restrict dst, const nk_char* nk_restrict src)
{
	return nki_strcat<nk_char>(dst, src);
}

nk_errno nk_strcat_s(nk_char* nk_restrict dst, nk_rsize dstsz, const nk_char* nk_restrict src)
{
	return nki_strcat_s<nk_char>(dst, dstsz, src);
}

nk_char* nk_strncat(nk_char* nk_restrict dst, const nk_char* nk_restrict src, nk_size count)
{
	return nki_strncat<nk_char>(dst, src, count);
}

nk_errno nk_strncat_s(nk_char* nk_restrict dst, nk_rsize dstsz, const nk_char* nk_restrict src, nk_rsize count)
{
	return nki_strncat_s<nk_char>(dst, dstsz, src, count);
}

nk_size nk_strlcat(nk_char* nk_restrict dst, const nk_char* nk_restrict src, nk_size count)
{
    return nki_strlcat<nk_char>(dst, src, count);
}

nk_size nk_strxfrm(nk_char* nk_restrict dst, const nk_char* nk_restrict src, nk_size count);

nk_size nk_strlen(const nk_char* str)
{
	return nki_strlen<nk_char>(str);
}

nk_size nk_strnlen(const nk_char* str, nk_size strsz)
{
	return nki_strnlen<nk_char>(str, strsz);
}

nk_size nk_strnlen_s(const nk_char* str, nk_size strsz)
{
	return nki_strnlen_s<nk_char>(str, strsz);
}

int nk_strcmp(const nk_char* lhs, const nk_char* rhs)
{
	return nki_strcmp<nk_char>(lhs, rhs);
}

int nk_strncmp(const nk_char* lhs, const nk_char* rhs, nk_size count)
{
	return nki_strncmp<nk_char>(lhs, rhs, count);
}

nk_char* nk_strchr(const nk_char* str, nk_cint ch)
{
	return nki_strchr<nk_char>(str, (nk_char)ch);
}

nk_char* nk_strrchr(const nk_char* str, nk_cint ch)
{
	return nki_strrchr<nk_char>(str, (nk_char)ch);
}

nk_char* nk_strnchr(const nk_char* str, const nk_char* find, nk_size count)
{
	return nki_strnrchr<nk_char>(str, find, count);
}

// nk_char8
nk_char8* nk_u8scpy(nk_char8* nk_restrict dst, const nk_char8* nk_restrict src)
{
	return nki_strcpy<nk_char8>(dst, src);
}

nk_char8* nk_u8sncpy(nk_char8* nk_restrict dst, const nk_char8* nk_restrict src, nk_size count)
{
	return nki_strncpy<nk_char8>(dst, src, count);
}

nk_char8* nk_u8scat(nk_char8* nk_restrict dst, const nk_char8* nk_restrict src)
{
	return nki_strcat<nk_char8>(dst, src);
}

nk_char8* nk_u8sncat(nk_char8* nk_restrict dst, const nk_char8* nk_restrict src, nk_size count)
{
	return nki_strncat<nk_char8>(dst, src, count);
}

nk_size nk_u8sxfrm(nk_char8* nk_restrict dst, const nk_char8* nk_restrict src, nk_size count);

nk_size nk_u8slen(const nk_char8* str)
{
	return nki_strlen<nk_char8>(str);
}

nk_size nk_u8slen_s(const nk_char8* str, nk_size strsz)
{
	return nki_strnlen_s<nk_char8>(str, strsz);
}

int nk_u8scmp(const nk_char8* lhs, const nk_char8* rhs)
{
	return nki_strcmp<nk_char8>(lhs, rhs);
}

int nk_u8sncmp(const nk_char8* lhs, const nk_char8* rhs, nk_size count)
{
	return nki_strncmp<nk_char8>(lhs, rhs, count);
}

nk_char8* nk_u8schr(const nk_char8* str, int ch)
{
	return nki_strchr<nk_char8>(str, (nk_char8)ch);
}

nk_char8* nk_u8srchr(const nk_char8* str, int ch)
{
	return nki_strrchr<nk_char8>(str, (nk_char8)ch);
}

// nk_char16
nk_char16* nk_u16scpy(nk_char16* nk_restrict dst, const nk_char16* nk_restrict src)
{
	return nki_strcpy<nk_char16>(dst, src);
}

nk_char16* nk_u16sncpy(nk_char16* nk_restrict dst, const nk_char16* nk_restrict src, nk_size count)
{
	return nki_strncpy<nk_char16>(dst, src, count);
}

nk_char16* nk_u16scat(nk_char16* nk_restrict dst, const nk_char16* nk_restrict src)
{
	return nki_strcat<nk_char16>(dst, src);
}

nk_char16* nk_u16sncat(nk_char16* nk_restrict dst, const nk_char16* nk_restrict src, nk_size count)
{
	return nki_strncat<nk_char16>(dst, src, count);
}

nk_size nk_u16sxfrm(nk_char16* nk_restrict dst, const nk_char16* nk_restrict src, nk_size count);

nk_size nk_u16slen(const nk_char16* str)
{
	return nki_strlen<nk_char16>(str);
}

nk_size nk_u16slen_s(const nk_char16* str, nk_size strsz)
{
	return nki_strnlen_s<nk_char16>(str, strsz);
}

int nk_u16scmp(const nk_char16* lhs, const nk_char16* rhs)
{
	return nki_strcmp<nk_char16>(lhs, rhs);
}

int nk_u16sncmp(const nk_char16* lhs, const nk_char16* rhs, nk_size count)
{
	return nki_strncmp<nk_char16>(lhs, rhs, count);
}

nk_char16* nk_u16schr(const nk_char16* str, int ch)
{
	return nki_strchr<nk_char16>(str, (nk_char16)ch);
}

nk_char16* nk_u16srchr(const nk_char16* str, int ch)
{
	return nki_strrchr<nk_char16>(str, (nk_char16)ch);
}

// nk_char32
nk_char32* nk_u32scpy(nk_char32* nk_restrict dst, const nk_char32* nk_restrict src)
{
	return nki_strcpy<nk_char32>(dst, src);
}

nk_char32* nk_u32sncpy(nk_char32* nk_restrict dst, const nk_char32* nk_restrict src, nk_size count)
{
	return nki_strncpy<nk_char32>(dst, src, count);
}

nk_char32* nk_u32scat(nk_char32* nk_restrict dst, const nk_char32* nk_restrict src)
{
	return nki_strcat<nk_char32>(dst, src);
}

nk_char32* nk_u32sncat(nk_char32* nk_restrict dst, const nk_char32* nk_restrict src, nk_size count)
{
	return nki_strncat<nk_char32>(dst, src, count);
}

nk_size nk_u32sxfrm(nk_char32* nk_restrict dst, const nk_char32* nk_restrict src, nk_size count);

nk_size nk_u32slen(const nk_char32* str)
{
	return nki_strlen<nk_char32>(str);
}

nk_size nk_u32slen_s(const nk_char32* str, nk_size strsz)
{
	return nki_strnlen_s<nk_char32>(str, strsz);
}

int nk_u32scmp(const nk_char32* lhs, const nk_char32* rhs)
{
	return nki_strcmp<nk_char32>(lhs, rhs);
}

int nk_u32sncmp(const nk_char32* lhs, const nk_char32* rhs, nk_size count)
{
	return nki_strncmp<nk_char32>(lhs, rhs, count);
}

nk_char32* nk_u32schr(const nk_char32* str, int ch)
{
	return nki_strchr<nk_char32>(str, (nk_char32)ch);
}

nk_char32* nk_u32srchr(const nk_char32* str, int ch)
{
	return nki_strrchr<nk_char32>(str, (nk_char32)ch);
}

// memory ops.
void* nk_memchr(const void* ptr, int ch, nk_size count)
{
	return nki_memchr(ptr, ch, count);
}

int nk_memcmp(const void* lhs, const void* rhs, nk_size count)
{
	return nki_memcmp(lhs, rhs, count);
}

void* nk_memset(void* dst, int ch, nk_size count)
{
	return nki_memset(dst, ch, count);
}

void* nk_memcpy(void* nk_restrict dst, const void* nk_restrict src, nk_size count)
{
	return nki_memcpy(dst, src, count);
}

void* nk_memmove(void* dst, const void* src, nk_size count)
{
	return nki_memmove(dst, src, count);
}
