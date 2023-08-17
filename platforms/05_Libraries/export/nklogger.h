/* SPDX-License-Identifier: MIT-0 */
/**
 * @file nklogger.h
 */
#ifndef NKLOGGER_H_
#define NKLOGGER_H_

#include <cstddef>
#include <cstdint>

#define NK_LOG_LEVEL_OFF    (0)
#define NK_LOG_LEVEL_EMERG  (1)
#define NK_LOG_LEVEL_ALERT  (2)
#define NK_LOG_LEVEL_FATAL  (3)
#define NK_LOG_LEVEL_ERROR  (4)
#define NK_LOG_LEVEL_WARN   (5)
#define NK_LOG_LEVEL_NOTICE (6)
#define NK_LOG_LEVEL_INFO   (7)
#define NK_LOG_LEVEL_DEBUG  (8)
#define NK_LOG_LEVEL_TRACE  (9)
#define NK_LOG_LEVEL_ALL    (10)

#ifndef NK_LOG_LEVEL_DEFAULT
#define NK_LOG_LEVEL_DEFAULT (NK_LOG_LEVEL_NOTICE)
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void nk_emerg(const char* fmt, ...); // [[noreturn]]
void nk_alert(const char* fmt, ...);
void nk_fatal(const char* fmt, ...); // [[noreturn]]
void nk_error(const char* fmt, ...);
void nk_warn(const char* fmt, ...);
void nk_notice(const char* fmt, ...);
void nk_info(const char* fmt, ...);
void nk_debug(const char* fmt, ...);
void nk_trace(const char* fmt, ...);

#ifdef __cplusplus
}
#endif // __cplusplus

#ifdef __cplusplus
namespace bm {
namespace NkLogger {

namespace NkLogLevel {
const static int OFF    = NK_LOG_LEVEL_OFF;
const static int EMERG  = NK_LOG_LEVEL_EMERG;
const static int ALERT  = NK_LOG_LEVEL_ALERT;
const static int FATAL  = NK_LOG_LEVEL_FATAL;
const static int ERROR  = NK_LOG_LEVEL_ERROR;
const static int WARN   = NK_LOG_LEVEL_WARN;
const static int NOTICE = NK_LOG_LEVEL_NOTICE;
const static int INFO   = NK_LOG_LEVEL_INFO;
const static int DEBUG  = NK_LOG_LEVEL_DEBUG;
const static int TRACE  = NK_LOG_LEVEL_TRACE;
const static int ALL    = NK_LOG_LEVEL_ALL;
} // NkLogLevel

struct NkString {
    size_t      size;
    const char* str;
};

class NkOutput {
public:
    static void func_write(const char* str, size_t sz);
    static int  log_level();
};

class NkOutputBase {
public:
    virtual ~NkOutputBase() {}
    virtual void func_write(const char* str, size_t sz) = 0;
    virtual int  log_level() = 0;
};

template <class Output>
class NkLoggerTmpl : public Output {
public:
    inline void log(int level, const char* str, size_t sz) {
        if (level >= this->log_level()) {
            this->func_write(str, sz);
        }
    }

    inline void fatal(const char* str, size_t sz) {
        log(NkLogLevel::FATAL, str, sz);
    }
    inline void fatal(NkString& str) {
        fatal(str.str, str.size);
    }

    inline void error(const char* str, size_t sz) {
        log(NkLogLevel::ERROR, str, sz);
    }
    inline void error(NkString& str) {
        error(str.str, str.size);
    }

    inline void warn(const char* str, size_t sz) {
        log(NkLogLevel::WARN, str, sz);
    }
    inline void warn(NkString& str) {
        warn(str.str, str.size);
    }

    inline void info(const char* str, size_t sz) {
        log(NkLogLevel::INFO, str, sz);
    }
    inline void info(NkString& str) {
        info(str.str, str.size);
    }

    inline void debug(const char* str, size_t sz) {
        log(NkLogLevel::DEBUG, str, sz);
    }
    inline void debug(NkString& str) {
        debug(str.str, str.size);
    }

    inline void trace(const char* str, size_t sz) {
        log(NkLogLevel::TRACE, str, sz);
    }
    inline void trace(NkString& str) {
        trace(str.str, str.size);
    }
};

} // namespace NkLogger
} // namespace bm
#endif // __cplusplus

#endif // NKLOGGER_H_
