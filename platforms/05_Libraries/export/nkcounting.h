/* SPDX-License-Identifier: CC0-1.0 */
#ifndef NK_COUNTING_H_
#define NK_COUNTING_H_

#ifdef __cplusplus
#include <cstddef>
#include <cstdint>
#else
#include <stddef.h>
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
namespace nk {

class Counting;
template <typename ValueT> class CountingSimple;
template <typename ValueT> class CountingSpecifyAverage;
template <typename ValueT> class CountingSpecifyRange;
template <typename ValueT> class CountingSpecifyRangeWithOutliner;
template <typename ValueT> class CountingHyperLogLog;
template <typename ValueT> class CountingWithValues;

class Counting {
public:
    using CountT = std::uint32_t;
    using TotalT = double;
    using AddrT  = std::uint8_t;
    using MaskT  = std::uint32_t;

public:
    Counting() : num_(0) {}
    CountT inc();
    CountT estimate() const;

public:
    CountT num_;
};

Counting::CountT Counting::inc()
{
    num_ += 1;
    return num_;
}

Counting::CountT Counting::estimate() const
{
    return num_;
}

template <typename ValueT>
class CountingSimple {
public:
    CountingSimple() : num_(0) {}

    Counting::CountT inc(ValueT value);
    Counting::CountT estimate() const;

    ValueT min() const;
    ValueT max() const;
    ValueT mean() const;

private:
    Counting::CountT num_;
    Counting::TotalT total_;

private:
    ValueT  min_;
    ValueT  max_;
};

template <typename ValueT>
Counting::CountT CountingSimple<ValueT>::inc(ValueT value)
{
    if (num_ == 0) {
        min_ = value;
        max_ = value;
        total_ = (Counting::TotalT)value;
        num_ = 1;
    }
    else {
        if (min_ > value) {
            min_ = value;
        }
        if (max_ < value) {
            max_ = value;
        }
        total_ = total_ + (Counting::TotalT)value;
        num_ += 1;
    }
    return num_;
}

template <typename ValueT>
ValueT CountingSimple<ValueT>::min() const
{
    return min_;
}

template <typename ValueT>
ValueT CountingSimple<ValueT>::max() const
{
    return max_;
}

template <typename ValueT>
ValueT CountingSimple<ValueT>::mean() const
{
    if (num_ == 0) {
        return (ValueT)0;
    }
    return (ValueT)(total_ / (Counting::TotalT)num_);
}

template <typename ValueT>
Counting::CountT CountingSimple<ValueT>::estimate() const
{
    return num_;
}

} // namespace nk
#endif

#endif /* NK_COUNTING_H_ */
