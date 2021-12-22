/**
 * @file nkstring.cpp
 * 
 */
#include "nkstring.h"
#include <array>
#include <cstdint>

// restrict keyword (C11)
#ifdef __cplusplus
#define nk_restrict
#else
#define nk_restrict restrict
#endif

namespace {

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

} // namespace

char* nk_strcpy(char* nk_restrict dst, const char* nk_restrict src)
{
	return nki_strcpy<char>(dst, src);
}

char* nk_strncpy(char* nk_restrict dst, const char* nk_restrict src, size_t count)
{
	return nki_strncpy<char>(dst, src, count);
}

char* nk_strcat(char* nk_restrict dst, const char* nk_restrict src)
{
	return nki_strcat<char>(dst, src);
}

char* nk_strncat(char* nk_restrict dst, const char* nk_restrict src, size_t count)
{
	return nki_strncat<char>(dst, src, count);
}

size_t nk_strxfrm(char* nk_restrict dst, const char* nk_restrict src, size_t count);

size_t nk_strlen(const char* str)
{
	return nki_strlen<char>(str);
}

size_t nk_strlen_s(const char* str, size_t strsz)
{
	return nki_strlen_s<char>(str, strsz);
}

int nk_strcmp(const char* lhs, const char* rhs)
{
	return nki_strcmp<char>(lhs, rhs);
}

int nk_strncmp(const char* lhs, const char* rhs, size_t count)
{
	return nki_strncmp<char>(lhs, rhs, count);
}

char* nk_strchr(const char* str, int ch)
{
	return nki_strchr<char>(str, (char)ch);
}

char* nk_strrchr(const char* str, int ch)
{
	return nki_strrchr<char>(str, (char)ch);
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
