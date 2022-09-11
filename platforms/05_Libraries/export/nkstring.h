/**
 * @file nkstring.h
 * 
 */
#ifndef NK_STRING_H_
#define NK_STRING_H_

#ifdef __cplusplus
#include <cstddef>
#include <cstdint>
#else
#include <stddef.h>
#include <stdint.h>
#endif

// char, char* [ASCII, MBCS, (UTF-8)]
// char8_t, char8_t* [UTF-8]
// char16_t, char16_t* [UTF-16]
// char32_t, char32_t* [UTF-32]
// whar_t, wchar_t*

// restrict keyword (C11)
#ifdef __cplusplus
#define nk_restrict
#else
#define nk_restrict restrict
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NK_STRING_OMIT_CHAR
char*  nk_strcpy(char* nk_restrict dst, const char* nk_restrict src);
char*  nk_strncpy(char* nk_restrict dst, const char* nk_restrict src, size_t count);
char*  nk_strcat(char* nk_restrict dst, const char* nk_restrict src);
char*  nk_strncat(char* nk_restrict dst, const char* nk_restrict src, size_t count);
size_t nk_strlen(const char* str);
size_t nk_strlen_s(const char* str, size_t strsz);
int    nk_strcmp(const char* lhs, const char* rhs);
int    nk_strncmp(const char* lhs, const char* rhs, size_t count);
char*  nk_strchr(const char* str, int ch);
char*  nk_strrchr(const char* str, int ch);
size_t nk_strspn(const char* dst, const char* src);
size_t nk_strcspn(const char* dst, const char* src);
char*  nk_strpbrk(const char* dst, const char* breakset);
char*  nk_strstr(const char* str, const char* substr);
char*  nk_strtok(char* nk_restrict str, const char* nk_restrict delim);
size_t nk_strxfrm(char* nk_restrict dst, const char* nk_restrict src, size_t count);
int    nk_strcoll(const char* lhs, const char* rhs);
#endif // NK_STRING_OMIT_CHAR

typedef uint32_t nk_mbstate;

int nk_mbsinit(const nk_mbstate* pst);

#ifndef NK_STRING_OMIT_CHAR8
typedef uint8_t nk_char8;

nk_char8* nk_u8strcpy(nk_char8* nk_restrict dst, const nk_char8* nk_restrict src);
nk_char8* nk_u8strncpy(nk_char8* nk_restrict dst, const nk_char8* nk_restrict src, size_t count);
nk_char8* nk_u8strcat(nk_char8* nk_restrict dst, const nk_char8* nk_restrict src);
nk_char8* nk_u8strncat(nk_char8* nk_restrict dst, const nk_char8* nk_restrict src, size_t count);
size_t    nk_u8strlen(const nk_char8* str);
size_t    nk_u8strlen_s(const nk_char8* str, size_t strsz);
int       nk_u8strcmp(const nk_char8* lhs, const nk_char8* rhs);
int       nk_u8strncmp(const nk_char8* lhs, const nk_char8* rhs, size_t count);
nk_char8* nk_u8strchr(const nk_char8* str, int ch);
nk_char8* nk_u8strrchr(const nk_char8* str, int ch);
size_t    nk_u8strspn(const nk_char8* dst, const nk_char8* src);
size_t    nk_u8strcspn(const nk_char8* dst, const nk_char8* src);
nk_char8* nk_u8strpbrk(const nk_char8* dst, const nk_char8* breakset);
nk_char8* nk_u8strstr(const nk_char8* str, const nk_char8* substr);
nk_char8* nk_u8strtok(nk_char8* nk_restrict str, const nk_char8* nk_restrict delim);
size_t    nk_u8strxfrm(nk_char8* nk_restrict dst, const nk_char8* nk_restrict src, size_t count);
int       nk_u8strcoll(const nk_char8* lhs, const nk_char8* rhs);

#endif // NK_STRING_OMIT_CHAR8

#ifndef NK_STRING_OMIT_CHAR16
typedef uint16_t nk_char16;

nk_char16* nk_u16strcpy(nk_char16* nk_restrict dst, const nk_char16* nk_restrict src);
nk_char16* nk_u16strncpy(nk_char16* nk_restrict dst, const nk_char16* nk_restrict src, size_t count);
nk_char16* nk_u16strcat(nk_char16* nk_restrict dst, const nk_char16* nk_restrict src);
nk_char16* nk_u16strncat(nk_char16* nk_restrict dst, const nk_char16* nk_restrict src, size_t count);
size_t     nk_u16strlen(const nk_char16* str);
size_t     nk_u16strlen_s(const nk_char16* str, size_t strsz);
int        nk_u16strcmp(const nk_char16* lhs, const nk_char16* rhs);
int        nk_u16strncmp(const nk_char16* lhs, const nk_char16* rhs, size_t count);
nk_char16* nk_u16strchr(const nk_char16* str, int ch);
nk_char16* nk_u16strrchr(const nk_char16* str, int ch);
size_t     nk_u16strspn(const nk_char16* dst, const nk_char16* src);
size_t     nk_u16strcspn(const nk_char16* dst, const nk_char16* src);
nk_char16* nk_u16strpbrk(const nk_char16* dst, const nk_char16* breakset);
nk_char16* nk_u16strstr(const nk_char16* str, const nk_char16* substr);
nk_char16* nk_u16strtok(nk_char16* nk_restrict str, const nk_char16* nk_restrict delim);
size_t     nk_u16strxfrm(nk_char16* nk_restrict dst, const nk_char16* nk_restrict src, size_t count);
int        nk_u16strcoll(const nk_char16* lhs, const nk_char16* rhs);

#endif // NK_STRING_OMIT_CHAR16

#ifndef NK_STRING_OMIT_CHAR32
typedef uint32_t nk_char32;

nk_char32* nk_u32strcpy(nk_char32* nk_restrict dst, const nk_char32* nk_restrict src);
nk_char32* nk_u32strncpy(nk_char32* nk_restrict dst, const nk_char32* nk_restrict src, size_t count);
nk_char32* nk_u32strcat(nk_char32* nk_restrict dst, const nk_char32* nk_restrict src);
nk_char32* nk_u32strncat(nk_char32* nk_restrict dst, const nk_char32* nk_restrict src, size_t count);
size_t     nk_u32strlen(const nk_char32* str);
size_t     nk_u32strlen_s(const nk_char32* str, size_t strsz);
int        nk_u32strcmp(const nk_char32* lhs, const nk_char32* rhs);
int        nk_u32strncmp(const nk_char32* lhs, const nk_char32* rhs, size_t count);
nk_char32* nk_u32strchr(const nk_char32* str, int ch);
nk_char32* nk_u32strrchr(const nk_char32* str, int ch);
size_t     nk_u32strspn(const nk_char32* dst, const nk_char32* src);
size_t     nk_u32strcspn(const nk_char32* dst, const nk_char32* src);
nk_char32* nk_u32strpbrk(const nk_char32* dst, const nk_char32* breakset);
nk_char32* nk_u32strstr(const nk_char32* str, const nk_char32* substr);
nk_char32* nk_u32strtok(nk_char32* nk_restrict str, const nk_char32* nk_restrict delim);
size_t     nk_u32strxfrm(nk_char32* nk_restrict dst, const nk_char32* nk_restrict src, size_t count);
int        nk_u23strcoll(const nk_char32* lhs, const nk_char32* rhs);

size_t nk_mbrtoc32(nk_char32* nk_restrict u32s, const char* nk_restrict mbs, size_t n, nk_mbstate* nk_restrict pst);
size_t nk_wcrtomb(char* nk_restrict mbs, nk_char32 c32, nk_mbstate* pst);

#endif // NK_STRING_OMIT_CHAR32

#ifndef NK_STRING_OMIT_WCHAR
typedef uint32_t nk_wchar;

nk_wchar* nk_wcsrcpy(nk_wchar* nk_restrict dst, const nk_wchar* nk_restrict src);
nk_wchar* nk_wcsncpy(nk_wchar* nk_restrict dst, const nk_wchar* nk_restrict src, size_t count);
nk_wchar* nk_wcscat(nk_wchar* nk_restrict dst, const nk_wchar* nk_restrict src);
nk_wchar* nk_wcsncat(nk_wchar* nk_restrict dst, const nk_wchar* nk_restrict src, size_t count);
size_t    nk_wcslen(const nk_wchar* str);
size_t    nk_wcslen_s(const nk_wchar* str, size_t strsz);
int       nk_wcscmp(const nk_wchar* lhs, const nk_wchar* rhs);
int       nk_wcsncmp(const nk_wchar* lhs, const nk_wchar* rhs, size_t count);
nk_wchar* nk_wcschr(const nk_wchar* str, int ch);
nk_wchar* nk_wcsrchr(const nk_wchar* str, int ch);
size_t    nk_wcsspn(const nk_wchar* dst, const nk_wchar* src);
size_t    nk_wcscspn(const nk_wchar* dst, const nk_wchar* src);
nk_wchar* nk_wcspbrk(const nk_wchar* dst, const nk_wchar* breakset);
nk_wchar* nk_wcsstr(const nk_wchar* str, const nk_wchar* substr);
nk_wchar* nk_wcstok(nk_wchar* nk_restrict str, const nk_wchar* nk_restrict delim);
size_t    nk_wcsxfrm(nk_wchar* nk_restrict dst, const nk_wchar* nk_restrict src, size_t count);
int       nk_wcscoll(const nk_wchar* lhs, const nk_wchar* rhs);

size_t nk_mbrtowc(nk_wchar* wcs, const char* mbs, size_t n, nk_mbstate* pst);
size_t nk_mbsrtowcs(nk_wchar* wcs, const char** src, size_t n, nk_mbstate* pst);
size_t nk_wcrtomb(char* mbs, nk_wchar wc, nk_mbstate* pst);
size_t nk_wcsrtombs(char* mbs, const nk_wchar** src, size_t n, nk_mbstate* pst);

#endif // NK_STRING_OMIT_WCHAR

void*  nk_memchr(const void* ptr, int ch, size_t count);
int    nk_memcmp(const void* lhs, const void* rhs, size_t count);
void*  nk_memset(void* dst, int ch, size_t count);
void*  nk_memcpy(void* nk_restrict dst, const void* nk_restrict src, size_t count);
void*  nk_memmove(void* dst, const void* src, size_t count);

#ifdef __cplusplus
} // extern "C"
#endif

#undef nk_restrict

#endif // NK_STRING_H_
