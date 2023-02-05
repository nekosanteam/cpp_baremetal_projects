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
    return ((r.wp == r.rp) || ((r.rp + 2 * r.ring.size()) == r.wp));
}

size_t get_room(const struct vring& r)
{
    if (r.rp < r.wp) {
        return (r.ring.size() + r.rp - r.wp);
    }
    else if (r.rp >= r.wp) {
        return (r.ring.size() + r.rp - r.wp);
    }
    else if ((r.rp + r.ring.size()) < r.wp) {
            return 0;
    }
    else {
        return (r.rp - r.wp - 1);
    }
    return (r.ring.size() + r.rp - r.wp);
}

size_t recv(struct vring& r, uint8_t* buf, size_t len)
{
    if (is_empty(r)) {
        return 0;
    }

    size_t ret;
    size_t tgt;
    // r.rp != r.wp;

    if (r.rp < r.wp) {
        if (r.wp <= r.ring.size()) {
            // [rp, wp)
            tgt = r.wp - r.rp;
            if (tgt > len) {
                tgt = len;
            }
            copy_n(r.ring[r.rp], tgt, &buf[0]);
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
        copy_n(r.ring[r.rp], tgt, &buf[0]);
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
    if (get_room(r) < len) {
        len = get_room(r);
        if (len == 0) {
            return 0;
        }
    }

    size_t ret;

    if ((r.ring.size() - r.wp) >= len) {
        copy_n(&buf[0], len, &r.ring[r.wp]);
        ret = len;
        r.wp += len;
    }
    else {
        size_t tgt;
        size_t wp;

        ret = 0;
        tgt = r.ring.size() - r.wp;
        copy_n(&buf[0], tgt, &r.ring[r.wp]);
        ret = tgt;
        len -= tgt;
        wp = r.wp + tgt;

        tgt = r.rp - (r.wp % r.ring.size());
        if (tgt > len) {
            tgt = len;
        }
        copy_n(&buf[ret], tgt, &r.ring[wp]);
        ret += tgt;
        len -= tgt;
        r.wp = tgt;
    }

    return ret;
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

    print_vring(ring);
    send(ring, bufA, 128);
    print_vring(ring);
    recv(ring, bufB, 128);
    print_vring(ring);

    return 0;
}
