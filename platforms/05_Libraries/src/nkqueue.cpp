// SPDX-License-Identifier: CC0-1.0
/**
 * @file nkfdtlib.cpp
 *
 */
#include "nkqueue.h"

#include <array>
#include <algorithm>
#include <cstdint>
#include <cstddef>
#include <cassert>

using std::array;
using std::copy_n;

struct vring {
    std::array<uint8_t, 128> ring;
    size_t wp;
    size_t rp;
};

bool is_empty(const struct vring& r)
{
    return ((r.rp == r.wp) || ((r.rp + 2 * r.ring.size()) == r.wp));
}

size_t get_room(const struct vring& r)
{
    //ensure(res: res>=0 && res<=r.ring.size());
    if (is_empty(r)) {
        return r.ring.size();
    }
    if (r.rp > r.wp) {
        return (r.rp - r.wp - 1);
    }
    if ((r.wp - r.rp) > r.ring.size()) {
        return ((r.wp - r.rp) % r.ring.size());
    }
    return (r.ring.size() - (r.wp - r.rp)); 
}

size_t recv(struct vring& r, uint8_t* buf, size_t len)
{
    if (is_empty(r)) {
        return 0;
    }

    size_t ret;
    if ((ret = (r.ring.size() - get_room(r))) < len) {
        len = ret;
    }

    size_t rp  = r.rp;
    size_t wp  = r.wp;
    size_t rrp = rp % r.ring.size();

    if (rp < wp) {
        if ((r.ring.size() - rrp) >= len) {
            copy_n(&r.ring[rrp], len, &buf[0]);
            rp = rp + len;
            if (rp == 2 * r.ring.size()) {
                rp = 0;
            }
        }
        else {
            size_t a = r.ring.size() - rrp;
            size_t b = len - a;
            copy_n(&r.ring[rrp], a, &buf[0]);
            copy_n(&r.ring[0], b, &buf[a]);
            rp = rp + len;
        }
    }
    else {
        if ((r.ring.size() - rrp) >= len) {
            copy_n(&r.ring[rrp], len, &buf[0]);
            rp = rp + len;
        }
        else {
            size_t a = r.ring.size() - rrp;
            size_t b = len - a;
            copy_n(&r.ring[rrp], a, &buf[0]);
            copy_n(&r.ring[0], b, &buf[a]);
            rp = b;
        }
    }
    r.rp = rp;
        
    return len;
}

size_t send(struct vring& r, const uint8_t* buf, size_t len)
{
    size_t ret;
    
    if ((ret = get_room(r)) < len) {
        len = ret;
        if (len == 0) {
            return 0;
        }
    }

    size_t wp  = r.wp;
    size_t rp  = r.rp;
    size_t rwp = wp % r.ring.size();
 
    if (rp <= wp) {
        if ((r.ring.size() - rwp) >= len) {
            copy_n(&buf[0], len, &r.ring[rwp]);
            if ((wp + len) > (2 * r.ring.size())) {
                wp = (wp + len) % (2 * r.ring.size());
            }
            else {
                wp = wp + len;
            }
        }
        else {
            size_t a = r.ring.size() - rwp;;
            size_t b = len - a;
            copy_n(&buf[0], a, &r.ring[rwp]);
            copy_n(&buf[a], b, &r.ring[0]);
            if ((wp + len) > (rp + r.ring.size())) {
                wp = b;
            }
            else {
                wp = wp + len;
            }
        }
    }
    else {
        copy_n(&buf[0], len, &r.ring[rwp]);
        wp = wp + len;
    }
    r.wp = wp;

    return len;
}

#undef NDEBUG
#include <cassert>
#include <cstdio>
#include <cstring>

void dump_buffer(uint8_t* buf, int len)
{
    for (int i=0; i<len; i++) {
        std::printf("%02x ", buf[i]);
        if ((i & 0x0F) == 0x0F) {
            std::printf("\n");
        }
    }
    std::printf("\n");
}

void print_vring(struct vring& r)
{
    for (int i=0; i<128; i++) {
        std::printf("%02x ", r.ring.at(i));
        if ((i & 0x0F) == 0x0F) {
            std::printf("\n");
        }
    }
    std::printf("wp = %ld\n", r.wp);
    std::printf("rp = %ld\n", r.rp);
    std::printf("empty = %d, get_room = %ld\n", is_empty(r), get_room(r));
    std::printf("\n");
    assert(get_room(r) <= r.ring.size());
    assert(r.wp <= 2*r.ring.size());
    assert(r.rp <  2*r.ring.size());
}

extern "C"
int nkqueue_test(int argc, char** argv)
{
    struct vring ring {};
    uint8_t bufA[128];
    uint8_t bufB[128];
    size_t  r;

    for (int i=0; i<128; i++) {
        bufA[i] = (char)i;
        bufB[i] = 0;
    }

    int t0;
    std::printf("t0\n");
    for (size_t i=0; i<256; i++) {
        send(ring, bufA, 128);
        recv(ring, bufB, 128);
        if ((t0 = std::memcmp(bufA, bufB, 128)) != 0) {
            std::printf("memcmp[%d] = %d\n", i, t0);
            print_vring(ring);
        }
    }

    int t1;
    std::printf("t1\n");
    for (size_t i=0; i<256; i++) {
        send(ring, bufA, 1);
        recv(ring, bufB, 1);
        if ((t1 = std::memcmp(bufA, bufB, 1)) != 0) {
            std::printf("memcmp[%d] = %d\n", i, t1);
            print_vring(ring);
        }
    }
 
    int t2;
    std::printf("t2\n");
    for (size_t i=0; i<256; i++) {
        for (size_t j=0; j<26; j++) {
            send(ring, bufA, j+1);
            //print_vring(ring);
            recv(ring, bufB, j+1);
            //print_vring(ring);
            if ((t2 = std::memcmp(bufA, bufB, j+1)) != 0) {
                dump_buffer(bufB, j+1);
                std::printf("memcmp[%d, %d] = %d\n", i, j, t2);
                print_vring(ring);
                return 1;
            }
            std::printf("check %d, %d\n", i, j);
        }
    }

    int t3;
    std::printf("t3\n");
    for (size_t i=0; i<256; i++) {
        for (size_t j=128; j>0; j++) {
            send(ring, bufA, j);
            recv(ring, bufB, j);
            if ((t3 = std::memcmp(bufA, bufB, j)) != 0) {
                dump_buffer(bufB, j);
                std::printf("memcmp[%d, %d] = %d\n", i, j, t3);
                print_vring(ring);
                return 1;
            }
        }
    }

    return 0;
}
