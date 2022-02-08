/**
 * @file nklogger.hpp
 * 
 */
#ifndef NKLOGGER_HPP_
#define NKLOGGER_HPP_

#include <cstddef>
#include <cstdint>

namespace bm {
namespace NkLogger {

namespace NkLogLevel {
const static int OFF   = 0;
const static int FATAL = 1;
const static int ERROR = 2;
const static int WARN  = 3;
const static int INFO  = 4;
const static int DEBUG = 5;
const static int TRACE = 6;
const static int ALL   = 7;
} // NkLogLevel

struct NkString {
    size_t      size;
    const char* str;
};

class NkOutput {
public:
    static void func_write(const char* str, size_t sz);
    const static int  log_level = NkLogLevel::ERROR;
};

template <class Output>
class NkLoggerTmpl : private Output {
public:
    static inline void log(int level, const char* str, size_t sz) {
        if (level >= Output::log_level) {
            Output::func_write(str, sz);
        }
    }

    static inline void fatal(const char* str, size_t sz) {
        log(NkLogLevel::FATAL, str, sz);
    }
    static inline void fatal(NkString& str) {
        fatal(str.str, str.size);
    }

    static inline void error(const char* str, size_t sz) {
        log(NkLogLevel::ERROR, str, sz);
    }
    static inline void error(NkString& str) {
        error(str.str, str.size);
    }

    static inline void warn(const char* str, size_t sz) {
        log(NkLogLevel::WARN, str, sz);
    }
    static inline void warn(NkString& str) {
        warn(str.str, str.size);
    }

    static inline void info(const char* str, size_t sz) {
        log(NkLogLevel::INFO, str, sz);
    }
    static inline void info(NkString& str) {
        info(str.str, str.size);
    }

    static inline void debug(const char* str, size_t sz) {
        log(NkLogLevel::DEBUG, str, sz);
    }
    static inline void debug(NkString& str) {
        debug(str.str, str.size);
    }

    static inline void trace(const char* str, size_t sz) {
        log(NkLogLevel::TRACE, str, sz);
    }
    static inline void trace(NkString& str) {
        trace(str.str, str.size);
    }
};

} // namespace NkLogger
} // namespace bm

#endif // NKLOGGER_HPP_
