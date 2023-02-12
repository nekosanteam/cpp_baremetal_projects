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
    if ((ret = (r.ring.size() - get_room(r))) <= len) {
        len = ret;
    }

    size_t rp;
    rp = r.rp;

    size_t tgt;

    if (r.rp < r.wp) {
        if ((r.wp - r.rp) <= len) {
            size_t rpp = (r.rp % r.ring.size());
            if ((rpp + len) < r.ring.size()) {
                copy_n(&r.ring[rpp], len, &buf[0]);
            }
            else {
                size_t a;
                size_t b;
                a = r.ring.size() - rpp;
                copy_n(&r.ring[rpp], a, &buf[0]);
                b = len - a;
                copy_n(&r.ring[0], a, &buf[a]);
                rp = rp + len;
            }

        }
        if (r.wp <= r.ring.size()) {
            // [rp, wp)
            tgt = r.wp - r.rp;
            if (tgt > len) {
                tgt = len;
            }
            copy_n(&r.ring[r.rp], tgt, &buf[0]);
            ret = tgt;
            r.rp += tgt;
        }
        // 0 < wp <= size() でまずは実装。
    }
    else {
        // [r.rp, size()) + [0, r.wp)
        size_t rp;
        tgt = r.ring.size() - r.rp;
        if (tgt > len) {
            tgt = len;
        }
        copy_n(&r.ring[r.rp], tgt, &buf[0]);
        len = len - tgt;
        ret = tgt;
        rp = (r.rp + tgt) % r.ring.size();

        tgt = r.wp - r.rp;
        if (tgt > len) {
            tgt = len;
        }
        copy_n(&r.ring[0], tgt, &buf[ret]);
        ret += tgt;
        r.rp = rp + tgt;
    }

    return ret;
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

    size_t wp;
    wp = r.wp % r.ring.size();

    if (r.rp <= r.wp) {
        if ((r.ring.size() - wp) >= len) {
            copy_n(&buf[0], len, &r.ring[wp]);
        }
        else {
            size_t a;
            size_t b;
            a = r.ring.size() - wp;
            copy_n(&buf[0], a, &r.ring[wp]);
            b = len - a;
            copy_n(&buf[a], b, &r.ring[0]);
        }
        if ((r.wp + len) >= (r.rp + r.ring.size())) {
            r.wp = wp + len;
        }
        else {
            r.wp = r.wp + len;
        }
    }
    else {
        copy_n(&buf[0], len, &r.ring[wp]);
        r.wp = r.wp + len;
    }

    return len;
}


#include <cstdio>
#include <cstring>

void dump_buffer(uint8_t* buf)
{
    for (int i=0; i<128; i++) {
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

//    print_vring(ring);
//    for (size_t i=0; i<128; i++) {
        send(ring, bufA, 128);
        print_vring(ring);
        recv(ring, bufB, 128);
        std::printf("cmp = %d\n", memcmp(bufA, bufB, 128));
        print_vring(ring);
        send(ring, bufA, 1);
        print_vring(ring);
        send(ring, bufA, 1);
        print_vring(ring);
        send(ring, bufA, 1);
        //recv(ring, bufB, 1);
        print_vring(ring);
//    }

    return 0;
}
