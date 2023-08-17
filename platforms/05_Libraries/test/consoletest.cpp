/* SPDX-License-Identifier: MIT-0 */
#include "nklogger.h"
#include "ntstdio.h"
#include <stdio.h>

namespace bm {
namespace NkLogger {

void NkOutput::func_write(const char* str, size_t sz)
{
    printf("%s", str);
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
    bm::NkLogger::NkLog log;
    log.info(str, sz);
}

int main(int argc, char** argv)
{
    puts_info("test\n", 6);
    return 0;
}
