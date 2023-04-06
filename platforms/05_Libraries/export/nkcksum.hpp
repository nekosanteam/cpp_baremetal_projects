/**
 * @file nkhash.hpp
 */
#ifndef NKHASH_HPP_
#define NKHASH_HPP_

#include <cstdint>

namespace bm {
namespace hash {

template <std::uint16_t p, std::uint16_t ini, bool ri, bool ro, std::uint16_t xo>
class crc16 {
public:
    const std::uint16_t poly{p};
    const std::uint16_t init{ini};
    const std::uint16_t xorout{xo};
    const bool          refin{ri};
    const bool          refout{ro};

public:
    static std::uint16_t update(std::size_t count, const std::uint8_t* buffer)
    {
        uint16_t r = init;
        while (count--) {
            r = ((r << 8) | *buffer) ^ table[(r >> 24) & 0xFF];
            buffer++;
        }
    }

};

std::uint16_t nk_crc16(std::size_t count, const std::uint8_t* buffer);

std::uint16_t nk_crc16C(std::size_t count, const std::uint8_t* buffer);



}
}

#endif /* NKHASH_HPP_ */
