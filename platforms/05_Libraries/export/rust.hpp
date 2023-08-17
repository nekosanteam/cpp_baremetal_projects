/* SPDX-License-Identifier: MIT-0 */
/**
 * @file rust.hpp
 */
#ifndef RUST_HPP_
#define RUST_HPP_

#include <cstdint>

namespace rust {

namespace types {
using u8   = std::uint8_t;
using u16  = std::uint16_t;
using u32  = std::uint32_t;
using u64  = std::uint64_t;
//using u128 = std::uint128_t;
using i8   = std::int8_t;
using i16  = std::int16_t;
using i32  = std::int32_t;
using i64  = std::int64_t;
//using i128 = std::int128_t;

using f32  = float;
using f64  = double;

//static_assert(sizeof(f32) == 4, "");
//static_assert(sizeof(f64) == 8, "");

using usize = std::size_t;
using isize = ssize_t;
}


}

#endif /* RUST_HPP_ */
