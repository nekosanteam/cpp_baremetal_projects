
#include <cstdint>

using std::size_t;
using std::uint64_t;
using std::uint8_t;

static inline uint64_t* memcpy16b_burst1(uint64_t* dst, uint64_t* src)
{
	uint64_t r0;
	uint64_t r1;

	asm volatile ("ldp %[r0], %[r1], [%[src]]\n\t"
	              "stp %[r0], %[r1], [%[dst]]"
	            : [r0] "=&r" (r0), [r1] "=&r" (r1), "=m" (*dst)
	            : [dst] "r" (dst), [src] "r" (src), "m" (*src)
	            : "memory");

	return dst;
}

static inline uint64_t* memcpy16b_burst2(uint64_t* dst, uint64_t* src)
{
	__uint128_t r0;
	__uint128_t r1;

	asm volatile ("ldp %q[r0], %q[r1], [%[src]]\n\t"
	              "stp %q[r0], %q[r1], [%[dst]]"
	            : [r0] "=&x" (r0), [r1] "=&x" (r1), "=m" (*dst)
	            : [dst] "r" (dst), [src] "r" (src), "m" (*src)
	            : "memory");

	return dst;
}

static inline uint64_t* memcpy16b_burst4(uint64_t* dst, uint64_t* src)
{
	asm volatile ("ld1 {v0.16b-v3.16b}, [%[src]]\n\t"
	              "st1 {v0.16b-v3.16b}, [%[dst]]"
	            : "=m" (*dst)
	            : [dst] "r" (dst), [src] "r" (src), "m" (*src)
	            : "v0", "v1", "v2", "v3", "memory");

	return dst;
}

void* memcpy16b_burstN(void* dst, void* src, unsigned int n)
{
	uint64_t* dst_u = reinterpret_cast<uint64_t*>(dst);
	uint64_t* src_u = reinterpret_cast<uint64_t*>(src);
	uint64_t* ret_u;

	switch (n) {
	case 1:
		ret_u = memcpy16b_burst1(dst_u, src_u);
		break;
	case 2:
		ret_u = memcpy16b_burst2(dst_u, src_u);
		break;
	case 4:
		ret_u = memcpy16b_burst4(dst_u, src_u);
		break;
	default:
		ret_u = nullptr;
		break;
	}

	return reinterpret_cast<void*>(ret_u);
}

void* memcpy16b(void* dst, void* src, size_t size)
{
	uint64_t* dst_u = reinterpret_cast<uint64_t*>(dst);
	uint64_t* src_u = reinterpret_cast<uint64_t*>(src);
	void*     ret   = dst;

	const size_t N = (size + 15)/16;

	for (size_t i=0; i<N; i+=1, dst_u+=2, src_u+=2) {
		dst = memcpy16b_burstN(dst_u, src_u, 1);
	}

	return ret;
}

void* memcpy32b(void* dst, void* src, size_t size)
{
	uint64_t* dst_u = reinterpret_cast<uint64_t*>(dst);
	uint64_t* src_u = reinterpret_cast<uint64_t*>(src);
	void*     ret   = dst;

	const size_t N = (size + 31) / 32;

	for (size_t i=0; i<N; i+=1, dst_u+=4, src_u+=4) {
		dst = memcpy16b_burstN(dst_u, src_u, 2);
	}

	return ret;
}

void* memcpy64b(void* dst, void* src, size_t size)
{
	uint64_t* dst_u = reinterpret_cast<uint64_t*>(dst);
	uint64_t* src_u = reinterpret_cast<uint64_t*>(src);
	void*     ret   = dst;

	const size_t N = (size + 63) / 64;

	for (size_t i=0; i<N; i+=1, dst_u+=8, src_u+=8) {
		dst = memcpy16b_burstN(dst_u, src_u, 4);
	}

	return ret;
}
