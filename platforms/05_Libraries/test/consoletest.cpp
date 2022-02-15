#include "nklogger.hpp"
#include "ntstdio.h"

namespace bm {
namespace NkLogger {

void NkOutput::func_write(const char* str, size_t sz)
{
}

int NkOutput::log_level()
{
    return NkLogLevel::INFO;
}

using NkLog = NkLoggerTmpl<NkOutput>;

} // namespace NkLogger
} // namespace bm

extern "C" {
void puts_info(const char*, size_t);
}

void puts_info(const char* str, size_t sz)
{
    bm::NkLogger::NkLog::info(str, sz);
}

int main(int argc, char** argv)
{
    puts_info("test", 5);
    return 0;
}
