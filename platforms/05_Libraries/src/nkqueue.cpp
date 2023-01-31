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

bool  is_empty(const struct vring& r)
{
    return (r.wp == r.rp);
}

size_t get_room(const struct vring& r)
{
    if (r.wp < r.rp) {
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

    if (r.wp > r.rp) {
        if (r.ring.size() > r.wp) {
            // [rp, wp)
            tgt = r.wp - r.rp;
            if (tgt > len) {
                tgt = len;
            }
            copy_n(r.ring.at(r.rp), len, &buf[0]);
            r.rp += tgt;
            ret = tgt;
        }
        else {
            // [r.rp, size()) + [0, r.wp-size())

        }
    }
    else {
        if (r.ring.size() > r.rp) {
            // [r.rp, size()) + [0, r.wp)

        }
        else {
            // [r.rp - size(), r.wp)
        }
    }

    return ret;
}

size_t send(struct vring& r, const uint8_t* buf, size_t len)
{
    if (get_room(r) >= len) {
        if ((r.ring.size() - r.wp) >= len) {
            std::copy(&r.ring[r.wp], buf, len);
        }
        else {

        }
    }
}
