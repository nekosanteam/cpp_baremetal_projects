#ifndef NKLOGGER_HPP_
#define NKLOGGER_HPP_

#include <cstddef>
#include <cstdint>

namespace bm {
namespace NkLogger {

class NkOutput {
public:
    static void func_write(char* str, size_t sz);
};

struct NkString {
    const char* str;
    size_t      size;
};

template <class Output>
class NkLoggerTmpl : private Output {
public:
    const static int OFF   = 0;
    const static int FATAL = 1;
    const static int ERROR = 2;
    const static int WARN  = 3;
    const static int INFO  = 4;
    const static int DEBUG = 5;
    const static int TRACE = 6;
    const static int ALL   = 7;

    static inline void log(int level, char* str, size_t sz) {
        Output::func_write(str, sz);
    }

    static inline void fatal(char* str, size_t sz) {
        log(FATAL, str, sz);
    }

    static inline void error(char* str, size_t sz) {
        log(ERROR, str, sz);
    }

    static inline void warn(char* str, size_t sz) {
        log(WARN, str, sz);
    }

    static inline void info(char* str, size_t sz) {
        log(INFO, str, sz);
    }

    static inline void debug(char* str, size_t sz) {
        log(DEBUG, str, sz);
    }

    static inline void trace(char* str, size_t sz) {
        log(TRACE, str, sz);
    }
};

} // namespace NkLogger
} // namespace bm

#endif // NKLOGGER_HPP_
