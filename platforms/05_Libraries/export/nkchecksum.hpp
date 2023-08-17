/* SPDX-License-Identifier: MIT-0 */
/**
 * @file nkchecksum.hpp
 */
#ifndef NKCHECKSUM_HPP_
#define NKCHECKSUM_HPP_

#include <cstdint>

namespace bm {
namespace checksum {

class checksum {
public:
	checksum() : value_(0) {}
	static void update(std::uint8_t* buf, std::size_t offset, std::size_t len);

public:
	std::uint_least8_t value_;
};

void checksum::update(std::uint8_t* buf, std::size_t offset, std::size_t len)
{
	for (std::size_t i=offset; i<(offset+len); i++) {
		value_ = value_ + buf[i]
	}
}

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

// RFC1950
static inline std::uint32_t adler32(std::uint8_t* data, std::size_t len)
{
    const std::uint64_t MOD_ADLER = 65521;
    const std::uint64_t CHUNK_LEN = 5552; // 255*n*(n+1)/2 + (n+1)*(mod-1) <= 2^32-1

    std::uint64_t a = 1;
    std::uint64_t b = 0;

    while (len > 0) {
        std::size_t tlen = (len > CHUNK_LEN) ? CHUNK_LEN : len;
        len -= tlen;
        while (tlen > 0) {
            a += *data;
            b += a;
            data++;
            tlen--;
        }
        a %= MOD_ADLER;
        b %= MOD_ADLER;
    }

    return (std::uint32_t)(((b << 16) | a) & 0xFFFFFFFFu);
}

}
}

#endif /* NKCHECKSUM_HPP_ */
