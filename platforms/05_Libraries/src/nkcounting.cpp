#include "nkcounting.h"

namespace nk {

Counting::CountT Counting::inc()
{
    num_ += 1;
    return num_;
}

Counting::CountT Counting::estimate() const
{
    return num_;
}


} // namespace nk
