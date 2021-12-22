/**
 * @file nkstring.h
 * 
 */
#ifndef NK_STRING_H__
#define NK_STRING_H__

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

#ifndef NK_STRING_OMIT_CHAR8

#endif // NK_STRING_OMIT_CHAR8

#ifndef NK_STRING_OMIT_CHAR16

#endif // NK_STRING_OMIT_CHAR16

#ifndef NK_STRING_OMIT_CHAR32

#endif // NK_STRING_OMIT_CHAR32

#ifndef NK_STRING_OMIT_WCHAR

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

#endif // NK_STRING_H__
