#include <cstdint>
#include <array>

// define
namespace nk {
namespace work {
namespace des {
using std::array;
using std::uint32_t;
using std::uint8_t;

using key_t = array<uint32_t, 2>;
using block_t = array<uint8_t, 8>;

block_t encode(key_t key, block_t block);
block_t decode(key_t key, block_t block);

}
}
}

// implementation
namespace nk {
namespace work {
namespace des {

uint8_t E[] = 
	{32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9,
	8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25, 
	24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};


block_t encode(key_t key, block_t block)
{

}

}
}
}
