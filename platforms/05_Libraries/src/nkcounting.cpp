#include "nkcounting.h"

namespace nk {
namespace work {

Counting::CountT Counting::inc()
{
    num_ += 1;
    return num_;
}

Counting::CountT Counting::estimate() const
{
    return num_;
}



} // namespace work
} // namespace nk
