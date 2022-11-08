/**
 * @file nkstring.h
 *
 */
#ifndef NK_STRING_H_
#define NK_STRING_H_

#ifdef __cplusplus
#include <cstddef>
#include <cstdint>
#include <array>
#else
#include <stddef.h>
#include <stdint.h>
#endif

// nk_char:   char,     char*     [ASCII, MBCS, UTF-8, str]
// nk_char8:  char8_t,  char8_t*  [UTF-8, u8s(tr)]
// nk_char16: char16_t, char16_t* [UTF-16, u16s(tr)]
// nk_char32: char32_t, char32_t* [UTF-32, u32s(tr)]
// nk_wchar:  wchar_t,  wchar_t*  [wchar, wcs(tr)]
// nk_ucs4:   UTF-32 charactor.

// restrict keyword (C11)
#ifdef __cplusplus
#define nk_restrict
#else
#define nk_restrict restrict
#endif

#ifdef __cplusplus
typedef std::size_t nk_size;
#else
typedef size_t nk_size;
#endif

#ifndef NK_RSIZE_MAX
#ifndef NK_OWN_RSIZE_MAX
#if !defined(NK_STRING_USE_RSIZE) || (NK_STRING_USE_RSIZE == 0)
typedef size_t nk_rsize;
#define NK_RSIZE_MAX (SIZE_MAX >> 1)
#else
typedef rsize_t nk_rsize;
#define NK_RSIZE_MAX (RSIZE_MAX)
#endif // NK_STRING_USE_RSIZE
#else
typedef NK_OWN_RSIZE_TYPE nk_rsize;
#define NK_RSIZE_MAX (NK_OWN_RSIZE_MAX)
#endif // NK_OWN_RSIZE_MAX
#endif // NK_RSIZE_MAX


#ifndef NK_EINVAL
#if !defined(NK_STRING_USE_ERRNO) || (NK_STRING_USE_ERRNO == 0)
typedef int nk_errno;
#define NK_EINVAL (-1)
#define NK_ERANGE (-2)
#else
#include <errno.h>
typedef errno_t nk_errno;
#define NK_EINVAL (EINVAL)
#define NK_ERANGE (ERANGE)
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t nk_ucs4;

#ifndef NK_STRING_OMIT_CHAR
typedef char nk_char;
typedef int  nk_cint;

// from C99 string.h.
nk_char* nk_strcpy(nk_char* nk_restrict dst, const nk_char* nk_restrict src);
nk_char* nk_strncpy(nk_char* nk_restrict dst, const nk_char* nk_restrict src, nk_size count);
nk_char* nk_strcat(nk_char* nk_restrict dst, const nk_char* nk_restrict src);
nk_char* nk_strncat(nk_char* nk_restrict dst, const nk_char* nk_restrict src, nk_size count);
nk_size  nk_strlen(const nk_char* str);
int      nk_strcmp(const nk_char* lhs, const nk_char* rhs);
int      nk_strncmp(const nk_char* lhs, const nk_char* rhs, nk_size count);
nk_char* nk_strchr(const nk_char* str, nk_cint ch);
nk_char* nk_strrchr(const nk_char* str, nk_cint ch);
nk_size  nk_strspn(const nk_char* dst, const nk_char* src);
nk_size  nk_strcspn(const nk_char* dst, const nk_char* src);
nk_char* nk_strpbrk(const nk_char* dst, const nk_char* breakset);
nk_char* nk_strstr(const nk_char* str, const nk_char* substr);
nk_size  nk_strxfrm(nk_char* nk_restrict dst, const nk_char* nk_restrict src, nk_size count);
// from POSIX.1-2008.
nk_size  nk_strnlen(const nk_char* str, nk_size maxsz);
// from C11.
nk_size  nk_strnlen_s(const nk_char* str, nk_size strsz);
nk_errno nk_strcpy_s(nk_char* nk_restrict dst, nk_rsize dstsz, const nk_char* nk_restrict src);
nk_errno nk_strncpy_s(nk_char* nk_restrict dst, nk_rsize dstsz, const nk_char* nk_restrict src, nk_rsize count);
nk_errno nk_strcat_s(nk_char* nk_restrict dst, nk_rsize dstsz, const nk_char* nk_restrict src);
nk_errno nk_strncat_s(nk_char* nk_restrict dst, nk_rsize dstsz, const nk_char* nk_restrict src, nk_rsize count);
nk_char* nk_strtok_s(nk_char* nk_restrict str, nk_rsize* nk_restrict strmax, const nk_char* nk_restrict delim, nk_char** nk_restrict ptr);
// from libbsd.
nk_size  nk_strlcpy(nk_char* nk_restrict dst, const nk_char* nk_restrict src, nk_size count);
nk_size  nk_strlcat(nk_char* nk_restrict dst, const nk_char* nk_restrict src, nk_size count);
nk_char* nk_strnstr(const nk_char* str, const nk_char* find, nk_size count);

// from libunistring.
nk_char* nk_strmove(nk_char* dst, const nk_char* src, nk_size count);
nk_char* nk_strset(nk_char* dst, nk_cint c, nk_size count);
nk_char* nk_stpcpy(nk_char* nk_restrict dst, const nk_char* nk_restrict src);
nk_char* nk_stpncpy(nk_char* nk_restrict dst, const nk_char* nk_restrict src, nk_size count);

const nk_char* nk_strcheck(const nk_char* str, nk_size count);

// inner use.
nk_size nk_strnlen_si(const nk_char* str, nk_size strsz);
nk_size nk_strcpy_si(nk_char* nk_restrict dst, nk_size dstsz, const nk_char* nk_restrict src, nk_size srcsz);
nk_size nk_strncpy_si(nk_char* nk_restrict dst, nk_size dstsz, const nk_char* nk_restrict src, nk_size srcsz);
nk_size nk_strncat_si(nk_char* nk_restrict dst, nk_size dstsz, const nk_char* nk_restrict src, nk_size srcsz);
#endif // NK_STRING_OMIT_CHAR

typedef uint32_t nk_mbstate;

int nk_mbsinit(const nk_mbstate* pst);

#ifndef NK_STRING_OMIT_CHAR8
typedef uint8_t nk_char8;
typedef int     nk_c8int;

nk_char8* nk_u8strcpy(nk_char8* nk_restrict dst, const nk_char8* nk_restrict src);
nk_char8* nk_u8strncpy(nk_char8* nk_restrict dst, const nk_char8* nk_restrict src, nk_size count);
nk_char8* nk_u8strcat(nk_char8* nk_restrict dst, const nk_char8* nk_restrict src);
nk_char8* nk_u8strncat(nk_char8* nk_restrict dst, const nk_char8* nk_restrict src, nk_size count);
nk_size   nk_u8strlen(const nk_char8* str);
nk_size   nk_u8strlen_s(const nk_char8* str, nk_size strsz);
int       nk_u8strcmp(const nk_char8* lhs, const nk_char8* rhs);
int       nk_u8strncmp(const nk_char8* lhs, const nk_char8* rhs, nk_size count);
nk_char8* nk_u8strchr(const nk_char8* str, int ch);
nk_char8* nk_u8strrchr(const nk_char8* str, int ch);
nk_size   nk_u8strspn(const nk_char8* dst, const nk_char8* src);
nk_size   nk_u8strcspn(const nk_char8* dst, const nk_char8* src);
nk_char8* nk_u8strpbrk(const nk_char8* dst, const nk_char8* breakset);
nk_char8* nk_u8strstr(const nk_char8* str, const nk_char8* substr);
nk_char8* nk_u8strtok(nk_char8* nk_restrict str, const nk_char8* nk_restrict delim);
nk_size   nk_u8strxfrm(nk_char8* nk_restrict dst, const nk_char8* nk_restrict src, nk_size count);
int       nk_u8strcoll(const nk_char8* lhs, const nk_char8* rhs);

nk_size   nk_mbrtoc8(nk_char8* nk_restrict c8s, const nk_char* nk_restrict mbs, nk_size n, nk_mbstate* nk_restrict pst);
nk_size   nk_c8rtomb(nk_char* nk_restrict mbs, nk_char8 c8, nk_mbstate* pst);

nk_char8* nk_u8strmove(nk_char8* dst, const nk_char8* src, nk_size count);
nk_char8* nk_u8strset(nk_char8* dst, nk_ucs4 ucs4, nk_size count);

const nk_char8* nk_u8scheck(const nk_char8* str, nk_size count);

// inner use.
nk_size nk_u8snlen_si(const nk_char8* str, nk_size strsz);
nk_size nk_u8scpy_si(nk_char8* nk_restrict dst, nk_size dstsz, const nk_char8* nk_restrict src, nk_size srcsz);
nk_size nk_u8sncpy_si(nk_char8* nk_restrict dst, nk_size dstsz, const nk_char8* nk_restrict src, nk_size srcsz);
nk_size nk_u8sncat_si(nk_char8* nk_restrict dst, nk_size dstsz, const nk_char8* nk_restrict src, nk_size srcsz);
#endif // NK_STRING_OMIT_CHAR8

#ifndef NK_STRING_OMIT_CHAR16
typedef uint16_t nk_char16;
typedef int32_t  nk_u16int;

nk_char16* nk_u16strcpy(nk_char16* nk_restrict dst, const nk_char16* nk_restrict src);
nk_char16* nk_u16strncpy(nk_char16* nk_restrict dst, const nk_char16* nk_restrict src, nk_size count);
nk_char16* nk_u16strcat(nk_char16* nk_restrict dst, const nk_char16* nk_restrict src);
nk_char16* nk_u16strncat(nk_char16* nk_restrict dst, const nk_char16* nk_restrict src, nk_size count);
nk_size    nk_u16strlen(const nk_char16* str);
nk_size    nk_u16strlen_s(const nk_char16* str, nk_size strsz);
int        nk_u16strcmp(const nk_char16* lhs, const nk_char16* rhs);
int        nk_u16strncmp(const nk_char16* lhs, const nk_char16* rhs, nk_size count);
nk_char16* nk_u16strchr(const nk_char16* str, int ch);
nk_char16* nk_u16strrchr(const nk_char16* str, int ch);
nk_size    nk_u16strspn(const nk_char16* dst, const nk_char16* src);
nk_size    nk_u16strcspn(const nk_char16* dst, const nk_char16* src);
nk_char16* nk_u16strpbrk(const nk_char16* dst, const nk_char16* breakset);
nk_char16* nk_u16strstr(const nk_char16* str, const nk_char16* substr);
nk_char16* nk_u16strtok(nk_char16* nk_restrict str, const nk_char16* nk_restrict delim);
nk_size    nk_u16strxfrm(nk_char16* nk_restrict dst, const nk_char16* nk_restrict src, nk_size count);
int        nk_u16strcoll(const nk_char16* lhs, const nk_char16* rhs);

nk_size    nk_mbrtoc16(nk_char16* nk_restrict c16s, const nk_char* nk_restrict mbs, nk_size n, nk_mbstate* nk_restrict pst);
nk_size    nk_c16rtomb(nk_char* nk_restrict mbs, nk_char16 c16, nk_mbstate* pst);
nk_size    nk_c8rtoc16(nk_char16* nk_restrict c16s, const nk_char8* nk_restrict c8s, nk_size n, nk_mbstate* nk_restrict pst);
nk_size    nk_c16rtoc8(nk_char8* nk_restrict c8s, nk_char16 c16, nk_mbstate* pst);

nk_char16* nk_u16strmove(nk_char16* dst, const nk_char16* src, nk_size count);
nk_char16* nk_u16strset(nk_char16* dst, nk_ucs4 ucs4, nk_size count);

const nk_char16* nk_u16scheck(const nk_char16* str, nk_size count);

// inner use.
nk_size nk_u16snlen_si(const nk_char16* str, nk_size strsz);
nk_size nk_u16scpy_si(nk_char16* nk_restrict dst, nk_size dstsz, const nk_char16* nk_restrict src, nk_size srcsz);
nk_size nk_u16sncpy_si(nk_char16* nk_restrict dst, nk_size dstsz, const nk_char16* nk_restrict src, nk_size srcsz);
nk_size nk_u16sncat_si(nk_char16* nk_restrict dst, nk_size dstsz, const nk_char16* nk_restrict src, nk_size srcsz);
#endif // NK_STRING_OMIT_CHAR16

#ifndef NK_STRING_OMIT_CHAR32
typedef uint32_t nk_char32;
typedef int32_t  nk_u32int;

nk_char32* nk_u32strcpy(nk_char32* nk_restrict dst, const nk_char32* nk_restrict src);
nk_char32* nk_u32strncpy(nk_char32* nk_restrict dst, const nk_char32* nk_restrict src, nk_size count);
nk_char32* nk_u32strcat(nk_char32* nk_restrict dst, const nk_char32* nk_restrict src);
nk_char32* nk_u32strncat(nk_char32* nk_restrict dst, const nk_char32* nk_restrict src, nk_size count);
nk_size    nk_u32strlen(const nk_char32* str);
nk_size    nk_u32strlen_s(const nk_char32* str, nk_size strsz);
int        nk_u32strcmp(const nk_char32* lhs, const nk_char32* rhs);
int        nk_u32strncmp(const nk_char32* lhs, const nk_char32* rhs, nk_size count);
nk_char32* nk_u32strchr(const nk_char32* str, int ch);
nk_char32* nk_u32strrchr(const nk_char32* str, int ch);
nk_size    nk_u32strspn(const nk_char32* dst, const nk_char32* src);
nk_size    nk_u32strcspn(const nk_char32* dst, const nk_char32* src);
nk_char32* nk_u32strpbrk(const nk_char32* dst, const nk_char32* breakset);
nk_char32* nk_u32strstr(const nk_char32* str, const nk_char32* substr);
nk_char32* nk_u32strtok(nk_char32* nk_restrict str, const nk_char32* nk_restrict delim);
nk_size    nk_u32strxfrm(nk_char32* nk_restrict dst, const nk_char32* nk_restrict src, nk_size count);
int        nk_u23strcoll(const nk_char32* lhs, const nk_char32* rhs);

nk_size    nk_mbrtoc32(nk_char32* nk_restrict c32s, const nk_char* nk_restrict mbs, nk_size n, nk_mbstate* nk_restrict pst);
nk_size    nk_c32rtomb(nk_char* nk_restrict mbs, nk_char32 c32, nk_mbstate* pst);
nk_size    nk_c8rtoc32(nk_char32* nk_restrict c32s, const nk_char8* nk_restrict c8s, nk_size n, nk_mbstate* nk_restrict pst);
nk_size    nk_c32rtoc8(nk_char8* nk_restrict c8s, nk_char32 c32, nk_mbstate* pst);

nk_char32* nk_u32strmove(nk_char32* dst, const nk_char32* src, nk_size count);
nk_char32* nk_u32strset(nk_char32* dst, nk_ucs4 ucs4, nk_size count);

const nk_char32* nk_u32scheck(const nk_char32* str, nk_size count);

// inner use.
nk_size nk_u32snlen_si(const nk_char32* str, nk_size strsz);
nk_size nk_u32scpy_si(nk_char32* nk_restrict dst, nk_size dstsz, const nk_char32* nk_restrict src, nk_size srcsz);
nk_size nk_u32sncpy_si(nk_char32* nk_restrict dst, nk_size dstsz, const nk_char32* nk_restrict src, nk_size srcsz);
nk_size nk_u32sncat_si(nk_char32* nk_restrict dst, nk_size dstsz, const nk_char32* nk_restrict src, nk_size srcsz);
#endif // NK_STRING_OMIT_CHAR32

#ifndef NK_STRING_OMIT_WCHAR
typedef uint32_t nk_wchar;
typedef int32_t  nk_wint;

nk_wchar* nk_wcsrcpy(nk_wchar* nk_restrict dst, const nk_wchar* nk_restrict src);
nk_wchar* nk_wcsncpy(nk_wchar* nk_restrict dst, const nk_wchar* nk_restrict src, nk_size count);
nk_wchar* nk_wcscat(nk_wchar* nk_restrict dst, const nk_wchar* nk_restrict src);
nk_wchar* nk_wcsncat(nk_wchar* nk_restrict dst, const nk_wchar* nk_restrict src, nk_size count);
nk_size   nk_wcslen(const nk_wchar* str);
nk_size   nk_wcslen_s(const nk_wchar* str, nk_size strsz);
int       nk_wcscmp(const nk_wchar* lhs, const nk_wchar* rhs);
int       nk_wcsncmp(const nk_wchar* lhs, const nk_wchar* rhs, nk_size count);
nk_wchar* nk_wcschr(const nk_wchar* str, int ch);
nk_wchar* nk_wcsrchr(const nk_wchar* str, int ch);
nk_size   nk_wcsspn(const nk_wchar* dst, const nk_wchar* src);
nk_size   nk_wcscspn(const nk_wchar* dst, const nk_wchar* src);
nk_wchar* nk_wcspbrk(const nk_wchar* dst, const nk_wchar* breakset);
nk_wchar* nk_wcsstr(const nk_wchar* str, const nk_wchar* substr);
nk_wchar* nk_wcstok(nk_wchar* nk_restrict str, const nk_wchar* nk_restrict delim);
nk_size   nk_wcsxfrm(nk_wchar* nk_restrict dst, const nk_wchar* nk_restrict src, nk_size count);
int       nk_wcscoll(const nk_wchar* lhs, const nk_wchar* rhs);

nk_size   nk_mbrtowc(nk_wchar* wcs, const nk_char* mbs, nk_size n, nk_mbstate* pst);
nk_size   nk_mbsrtowcs(nk_wchar* wcs, const nk_char** src, nk_size n, nk_mbstate* pst);
nk_size   nk_wcrtomb(nk_char* mbs, nk_wchar wc, nk_mbstate* pst);
nk_size   nk_wcsrtombs(nk_char* mbs, const nk_wchar** src, nk_size n, nk_mbstate* pst);

nk_wchar* nk_wcsmove(nk_wchar* dst, const nk_wchar* src, nk_size count);
nk_wchar* nk_wcsset(nk_wchar* dst, nk_wint wc, nk_size count);

const nk_wchar* nk_wcscheck(const nk_wchar* str, nk_size count);

// inner use.
nk_size nk_wcsnlen_si(const nk_wchar* str, nk_size strsz);
nk_size nk_wcscpy_si(nk_wchar* nk_restrict dst, nk_size dstsz, const nk_wchar* nk_restrict src, nk_size srcsz);
nk_size nk_wcsncpy_si(nk_wchar* nk_restrict dst, nk_size dstsz, const nk_wchar* nk_restrict src, nk_size srcsz);
nk_size nk_wcsncat_si(nk_wchar* nk_restrict dst, nk_size dstsz, const nk_wchar* nk_restrict src, nk_size srcsz);
#endif // NK_STRING_OMIT_WCHAR

#ifndef NK_STRING_OMIT_MEMORY

void*     nk_memchr(const void* ptr, int ch, nk_size count);
int       nk_memcmp(const void* lhs, const void* rhs, nk_size count);
void*     nk_memset(void* dst, int ch, nk_size count);
void*     nk_memcpy(void* nk_restrict dst, const void* nk_restrict src, nk_size count);
void*     nk_memmove(void* dst, const void* src, nk_size count);
// from C11.
nk_errno  nk_memset_s(void* dst, nk_rsize dstsz, int ch, nk_rsize count);
nk_errno  nk_memcpy_s(void* nk_restrict dst, nk_rsize dstsz, const void* nk_restrict src, nk_rsize count);
nk_errno  nk_memmove_s(void* dst, nk_rsize dstsz, const void* src, nk_rsize count);

#endif // NK_STRING_OMIT_MEMORY

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
namespace nk {

namespace nk_inner {
nk_size nk_strcpy_si(nk_char*, nk_size, const nk_char*, nk_size);
nk_size nk_strncpy_si(nk_char*, nk_size, const nk_char*, nk_size);
nk_size nk_strncat_si(nk_char*, nk_size, const nk_char*, nk_size);
nk_size nk_strnlen_si(nk_char*, nk_size);
nk_size nk_strcpy_si(nk_char8*, nk_size, const nk_char8*, nk_size);
nk_size nk_strncpy_si(nk_char8*, nk_size, const nk_char8*, nk_size);
nk_size nk_strncat_si(nk_char8*, nk_size, const nk_char8*, nk_size);
nk_size nk_strnlen_si(nk_char8*, nk_size);
nk_size nk_strcpy_si(nk_char16*, nk_size, const nk_char16*, nk_size);
nk_size nk_strncpy_si(nk_char16*, nk_size, const nk_char16*, nk_size);
nk_size nk_strncat_si(nk_char16*, nk_size, const nk_char16*, nk_size);
nk_size nk_strnlen_si(nk_char16*, nk_size);
nk_size nk_strcpy_si(nk_char32*, nk_size, const nk_char32*, nk_size);
nk_size nk_strncpy_si(nk_char32*, nk_size, const nk_char32*, nk_size);
nk_size nk_strncat_si(nk_char32*, nk_size, const nk_char32*, nk_size);
nk_size nk_strnlen_si(nk_char32*, nk_size);
nk_size nk_strcpy_si(nk_wchar*, nk_size, const nk_wchar*, nk_size);
nk_size nk_strncpy_si(nk_wchar*, nk_size, const nk_wchar*, nk_size);
nk_size nk_strncat_si(nk_wchar*, nk_size, const nk_wchar*, nk_size);
nk_size nk_strnlen_si(nk_wchar*, nk_size);
}

template <nk_size M>
static inline nk_size strlen(const std::array<nk_char, M>& str)
{
    return nk_strnlen_si(str.data(), str.size());
}

template <nk_size M>
static inline nk_size strlen(const nk_char (&str)[M])
{
    return nk_strnlen_si(&str[0], M);
}

template <nk_size M, nk_size N>
static inline nk_size strcpy(std::array<nk_char, M>& dst, const std::array<nk_char, N>& src)
{
    return nk_strcpy_si(dst.data(), dst.size(), src.data(), src.size());
}

template <nk_size M>
static inline nk_size strcpy(std::array<nk_char, M>& dst, const nk_char* src, nk_size srcsz)
{
    return nk_strcpy_si(dst.data(), dst.size(), src, srcsz);
}

template <nk_size M>
static inline nk_size strcpy(std::array<nk_char, M>& dst, const nk_char* src)
{
    nk_size srcsz = (NK_RSIZE_MAX/sizeof(nk_char));
    return nk_strcpy_si(dst.data(), dst.size(), src, srcsz);
}

template <nk_size M, nk_size N>
static inline nk_size strcpy(nk_char (&dst)[M], const nk_char (&src)[N])
{
    return nk_strcpy_si(&dst[0], M, &src[0], N);
}

template <nk_size M>
static inline nk_size strcpy(nk_char (&dst)[M], const nk_char* src, nk_size srcsz)
{
    return nk_strcpy_si(&dst[0], M, src, srcsz);
}

template <nk_size M>
static inline nk_size strcpy(nk_char (&dst)[M], const nk_char* src)
{
    nk_size srcsz = (NK_RSIZE_MAX/sizeof(nk_char));
    return nk_strcpy_si(&dst[0], M, src, srcsz);
}

template <nk_size M, nk_size N>
static inline nk_size strncpy(std::array<nk_char, M>& dst, const std::array<nk_char, N>& src)
{
    return nk_strncpy_si(dst.data(), dst.size(), src.data(), src.size());
}

template <nk_size M>
static inline nk_size strncpy(std::array<nk_char, M>& dst, const nk_char* src, nk_size srcsz)
{
    return nk_strncpy_si(dst.data(), dst.size(), src, srcsz);
}

template <nk_size M>
static inline nk_size strncpy(std::array<nk_char, M>& dst, const nk_char* src)
{
    nk_size srcsz = (NK_RSIZE_MAX/sizeof(nk_char));
    return nk_strncpy_si(dst.data(), dst.size(), src, srcsz);
}

template <nk_size M, nk_size N>
static inline nk_size strncpy(nk_char (&dst)[M], const nk_char (&src)[N])
{
    return nk_strncpy_si(&dst[0], M, &src[0], N);
}

template <nk_size M>
static inline nk_size strncpy(nk_char (&dst)[M], const nk_char* src, nk_size srcsz)
{
    return nk_strncpy_si(&dst[0], M, src, srcsz);
}

template <nk_size M>
static inline nk_size strncpy(nk_char (&dst)[M], const nk_char* src)
{
    nk_size srcsz = (NK_RSIZE_MAX/sizeof(nk_char));
    return nk_strncpy_si(&dst[0], M, src, srcsz);
}

template <nk_size M, nk_size N>
static inline nk_size strcat(std::array<nk_char, M>& dst, const std::array<nk_char, N>& src)
{
    nk_size pos = nk_strnlen(dst.data(), dst.size());
    return (pos + nk_strcpy_si(dst.data() + pos, dst.size() - pos, src.data(), src.size()));
}

template <nk_size M>
static inline nk_size strcat(std::array<nk_char, M>& dst, const nk_char* src, nk_size srcsz)
{
    nk_size pos = nk_strnlen(dst.data(), dst.size());
    return (pos + nk_strcpy_si((dst.data() + pos), (dst.size() - pos), src, srcsz));
}

template <nk_size M>
static inline nk_size strcat(std::array<nk_char, M>& dst, const nk_char* src)
{
    nk_size srcsz = (NK_RSIZE_MAX/sizeof(nk_char));
    nk_size pos   = nk_strnlen(dst.data(), dst.size());
    return (pos + nk_strcpy_si(dst.data() + pos, dst.size() - pos, src, srcsz));
}

template <nk_size M, nk_size N>
static inline nk_size strcat(nk_char (&dst)[M], const nk_char (&src)[N])
{
    nk_size pos = nk_strnlen(&dst[0], M);
    return (pos + nk_strcpy_si(&dst[pos], (M - pos), &src[0], N));
}

template <nk_size M>
static inline nk_size strcat(nk_char (&dst)[M], const nk_char* src, nk_size srcsz)
{
    nk_size pos = nk_strnlen(&dst[0], M);
    return (pos + nk_strcpy_si(&dst[pos], (M - pos), src, srcsz));
}

template <nk_size M>
static inline nk_size strcat(nk_char (&dst)[M], const nk_char* src)
{
    nk_size srcsz = (NK_RSIZE_MAX/sizeof(nk_char));
    nk_size pos   = nk_strnlen(&dst[0], M);
    return (pos + nk_strcpy_si(&dst[pos], (M - pos), src, srcsz));
}

template <nk_size M, nk_size N>
static inline nk_size strncat(std::array<nk_char, M>& dst, const std::array<nk_char, N>& src, nk_size count)
{
    nk_size pos = nk_strnlen(dst.data(), dst.size());
    return (pos + nk_strncat_si((dst.data() + pos), (dst.size() - pos), src, count));
}

template <nk_size M>
static inline nk_size strncat(std::array<nk_char, M>& dst, const nk_char* src, nk_size count)
{
    nk_size pos = nk_strnlen(dst.data(), dst.size());
    return (pos + nk_strncat_si((dst.data() + pos), (dst.size() - pos), src, count));
}

template <nk_size M, nk_size N>
static inline nk_size strncat(nk_char (&dst)[M], const nk_char (&src)[N], nk_size count)
{
    nk_size pos = nk_strnlen(&dst[0], M);
    return (pos + nk_strncat_si(&dst[pos], (M - pos), &src[0], count));
}

template <nk_size M>
static inline nk_size strncat(nk_char (&dst)[M], const nk_char* src, nk_size count)
{
    nk_size pos = nk_strnlen(&dst[0], M);
    return (pos + nk_strncat_si(&dst[pos], (M - pos), &src[0], count));
}

}
#endif

#endif // NK_STRING_H_
