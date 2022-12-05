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

using CountT = std::uint32_t;

template <typename ValueT>
class CountingHash {
public:
    static CountT hash(ValueT value);
};

template <typename ValueT>
class Counting {
public:
    virtual int update(ValueT value) = 0;
    virtual int estimate() = 0;

};

template <typename ValueT>
class CountingSimple : Counting<ValueT> {
public:
    CountingSimple() : num_(0) {}

    int    update(ValueT value) override;
    int    estimate() override;
    ValueT min();
    ValueT max();
    ValueT mean();

public:
    using total_t = double;

private:
    total_t  total_;
    uint32_t num_;
    ValueT   min_;
    ValueT   max_;
};

template <typename ValueT>
int CountingSimple<ValueT>::update(ValueT value)
{
    if (num_ == 0) {
        min_ = value;
        max_ = value;
        total_ = (total_t)value;
        num_++;
    }
    else {
        if (min_ > value) {
            min_ = value;
        }
        if (max_ < value) {
            max_ = value;
        }
        total_ = total_ + (total_t)value;
        num_++;
    }
    return 0;
}

template <typename ValueT>
ValueT CountingSimple<ValueT>::min()
{
    return min_;
}

template <typename ValueT>
ValueT CountingSimple<ValueT>::max()
{
    return max_;
}

template <typename ValueT>
ValueT CountingSimple<ValueT>::mean()
{
    if (num_ == 0) {
        return (ValueT)0;
    }
    return (ValueT)(total_ / (total_t)num_);
}

template <typename ValueT>
int CountingSimple<ValueT>::estimate()
{
    return 0;
}

} // namespace nk
#endif

#endif /* NK_COUNTING_H_ */
