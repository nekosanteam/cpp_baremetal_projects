#include "nkstring.h"
#include <array>
#include <cstdint>

namespace {

template <typename AccType>
static inline AccType* nki_strcpy(AccType* dst, const AccType* src)
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
static inline AccType* nki_strncpy(AccType* dst, const AccType* src, size_t count)
{
	AccType* ptr = dst;
	size_t   i   = 0;

    if (dst == NULL) {
        return NULL;
    }

    if (src != NULL) {
    	while (i<count) {
	    	*ptr = *src;
		    if (*src == (AccType)'\0') {
			    break;
            }
	    	ptr++;
		    src++;
            i++;
	    }
    }
    while (i<count) {
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
static inline AccType* nki_strcat(AccType* dst, const AccType* src)
{
    size_t pos = nki_strlen<AccType>(dst);
    (void)nki_strcpy<AccType>((dst + pos), src);
    return dst;
}

template <typename AccType>
static inline AccType* nki_strncat(AccType* dst, const AccType* src, size_t count)
{
    size_t pos = nki_strlen<AccType>(dst);
    (void)nki_strncpy<AccType>((dst + pos), src, count);
    *(dst + pos + count) = '\0';
    return dst;
}

} // namespace

// restrict keyword (C11)
#ifdef __cplusplus
#define nk_restrict
#else
#define nk_restrict restrict
#endif

char* nk_strcpy(char* nk_restrict dst, const char* nk_restrict src)
{
	return nki_strcpy<char>(dst, src);
}

char* nk_strncpy(char* nk_restrict dst, const char* nk_restrict src, size_t count)
{
    return nki_strncpy<char>(dst, src, count);
}

char*  nk_strcat(char* nk_restrict dst, const char* nk_restrict src)
{
    return nki_strcat(dst, src);
}

char*  nk_strncat(char* nk_restrict dst, const char* nk_restrict src, size_t count)
{
    return nki_strncat(dst, src, count);
}

size_t nk_strxfrm(char* nk_restrict dst, const char* nk_restrict src, size_t count);

size_t nk_strlen(const char* str)
{
    return nki_strlen(str);
}

size_t nk_strlen_s(const char* str, size_t strsz)
{
    return nki_strlen_s(str, strsz);
}

#undef nk_restrict
