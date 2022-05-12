#pragma once
/**
 * @file bm/log_c.h
 * 
 */
#include <stdarg.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void bm_fatal(const char* fmt, ...);
void bm_error(const char* fmt, ...);
void bm_warn(const char* fmt, ...);
void bm_notice(const char* fmt, ...);
void bm_info(const char* fmt, ...);
void bm_debug(const char* fmt, ...);
void bm_trace(const char* fmt, ...);

#define BM_LOG_LEVEL_NONE   (0)
#define BM_LOG_LEVEL_FATAL  (1)
#define BM_LOG_LEVEL_ERROR  (2)
#define BM_LOG_LEVEL_WARN   (3)
#define BM_LOG_LEVEL_NOTICE (4)
#define BM_LOG_LEVEL_INFO   (5)
#define BM_LOG_LEVEL_DEBUG  (6)
#define BM_LOG_LEVEL_TRACE  (7)
#define BM_LOG_LEVEL_ALL    (8)
#define BM_LOG_LEVEL_END    (9)

void bm_log_outputV(int level, const char* fmt, va_list varg);

#ifdef __cplusplus
} // extern "C"
#endif
