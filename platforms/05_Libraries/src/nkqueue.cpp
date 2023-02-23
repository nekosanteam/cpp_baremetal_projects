// SPDX-License-Identifier: CC0-1.0
/**
 * @file nkqueue.cpp
 *
 */
#include "nkqueue.h"

#include <array>
#include <algorithm>
#include <cstdint>
#include <cstddef>

#undef NDEBUG
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
    size_t rp = r.rp;
    size_t wp = r.wp;

    return (rp == wp);
}

size_t get_room(const struct vring& r)
{
    size_t rp = r.rp;
    size_t wp = r.wp;
    assert((rp < 2*r.ring.size()));
    assert((wp < 2*r.ring.size()));

    if (rp == wp) {
        return r.ring.size();
    }
    if (rp < wp) {
        assert(((rp + r.ring.size()) >= wp));
        return ((rp + r.ring.size()) - wp);
    }
    else {
        assert((rp >= (wp + r.ring.size())));
        return (rp - r.ring.size() - wp);
    }
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

    size_t rrp;
    if (rp < r.ring.size()) {
        rrp = rp;
    }
    else {
        rrp = rp - r.ring.size();
    }

    if ((rp + len) < 2 * r.ring.size()) {
        rp = rp + len;
    }
    else {
        assert(rp >= r.ring.size());
        rp = ((rp - r.ring.size()) + len) - r.ring.size();
    }

    if ((r.ring.size() - rrp) >= len) {
        copy_n(&r.ring[rrp], len, &buf[0]);
    }
    else {
        size_t a = r.ring.size() - rrp;
        size_t b = len - a;
        copy_n(&r.ring[rrp], a, &buf[0]);
        copy_n(&r.ring[0], b, &buf[a]);
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

    size_t rwp;
    if (wp < r.ring.size()) {
        rwp = wp;
    }
    else {
        rwp = wp - r.ring.size();
    }

    if ((wp + len) < 2 * r.ring.size()) {
        wp = wp + len;
    }
    else {
        assert(wp >= r.ring.size());
        wp = ((wp - r.ring.size()) + len) - r.ring.size();
    }

    if ((r.ring.size() - rwp) >= len) {
        copy_n(&buf[0], len, &r.ring[rwp]);
    }
    else {
        size_t a = r.ring.size() - rwp;;
        size_t b = len - a;
        copy_n(&buf[0], a, &r.ring[rwp]);
        copy_n(&buf[a], b, &r.ring[0]);
    }
    r.wp = wp;

    return len;
}

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
    assert(r.wp < 2*r.ring.size());
    assert(r.rp < 2*r.ring.size());
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
        for (size_t j=0; j<128; j++) {
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
            //std::printf("check %4d, %4d, get_room(%4d), rp %4ld, wp %4ld\n", i, j, get_room(ring), ring.rp, ring.wp);
        }
    }

    int t3;
    std::printf("t3\n");
    for (size_t i=0; i<256; i++) {
        for (size_t j=128; j>0; j--) {
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

    std::printf("done\n");
    return 0;
}
