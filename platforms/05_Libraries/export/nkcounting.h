/* SPDX-License-Identifier: MIT-0 */
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
namespace work {

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
    using AddrT  = std::uint16_t;
    using MaskT  = std::uint32_t;

public:
    Counting() : num_(0) {}
    CountT inc();
    CountT estimate() const;

public:
    CountT num_;
};

template <typename ValueT>
class CountingSimple {
public:
    CountingSimple() : num_(0) {}

    Counting::CountT inc(ValueT value);
    Counting::CountT estimate() const;

    ValueT min()  const;
    ValueT max()  const;
    ValueT mean() const;

private:
    Counting::CountT num_;
    Counting::TotalT total_;

private:
    ValueT min_;
    ValueT max_;
};

template <typename ValueT>
Counting::CountT CountingSimple<ValueT>::inc(ValueT value)
{
    if (num_ == 0) {
        min_   = value;
        max_   = value;
        total_ = static_cast<Counting::TotalT>(value);
        num_   = 1;
    }
    else {
        if (min_ > value) {
            min_ = value;
        }
        if (max_ < value) {
            max_ = value;
        }
        total_ = total_ + static_cast<Counting::TotalT>(value);
        num_   += 1;
    }
    return num_;
}

template <typename ValueT>
ValueT CountingSimple<ValueT>::min() const
{
    if (num_ == 0) {
        return static_cast<ValueT>(0);
    }
    return min_;
}

template <typename ValueT>
ValueT CountingSimple<ValueT>::max() const
{
    if (num_ == 0) {
        return static_cast<ValueT>(0);
    }
    return max_;
}

template <typename ValueT>
ValueT CountingSimple<ValueT>::mean() const
{
    if (num_ == 0) {
        return static_cast<ValueT>(0);
    }
    return static_cast<ValueT>(total_ / static_cast<Counting::TotalT>(num_));
}

template <typename ValueT>
Counting::CountT CountingSimple<ValueT>::estimate() const
{
    return num_;
}

template <typename ValueT>
class CountingSpecifyAverage {
public:
    CountingSpecifyAverage(ValueT average) : counts(), ave_(average) {}

    Counting::CountT inc(ValueT value) { return counts.inc(value - ave_); };
    Counting::CountT estimate() const { return counts.estimate(); }

    ValueT min() const  { return counts.min() + ave_;  }
    ValueT max() const  { return counts.max() + ave_;  }
    ValueT mean() const { return counts.mean() + ave_; }

private:
    CountingSimple<ValueT> counts;
    ValueT ave_;
};

template <typename ValueT>
class CountingSpecifyRange {
public:
    CountingSpecifyRange(ValueT llimit, ValueT hlimit) : counts(), llimit_(llimit), hlimit_(hlimit), buf_(nullptr) {}

    Counting::CountT inc(ValueT value) { return counts.inc(value); };
    Counting::CountT estimate() const { return counts.estimate(); }

    ValueT min() const  { return counts.min(); }
    ValueT max() const  { return counts.max(); }
    ValueT mean() const { return counts.mean(); }

    std::size_t bufferSize(ValueT gap) { gap_ = gap; return ((hlimit_ - llimit_) / gap_); }
    void setBuffer(Counting::CountT* buf) { buf_ = buf; }

private:
    CountingSimple<ValueT> counts;
    ValueT llimit_;
    ValueT hlimit_;
    Counting::CountT* buf_;
    ValueT gap_;
};

} // namespace work
} // namespace nk
#endif

#endif /* NK_COUNTING_H_ */
