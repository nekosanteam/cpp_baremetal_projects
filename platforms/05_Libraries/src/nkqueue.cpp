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
    // wp != rp;

    if (r.rp < r.wp) {
        if (r.wp <= r.ring.size()) {
            // [rp, wp)
            tgt = r.wp - r.rp;
            if (tgt > len) {
                tgt = len;
            }
            copy_n(r.ring.at(r.rp), tgt, &buf[0]);
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
        copy_n(r.ring.at(r.rp), tgt, &buf[0]);
        len = len - tgt;
        ret = tgt;
        rp = (r.rp + tgt) % r.ring.size();

        tgt = r.wp - r.rp;
        if (tgt > len) {
            tgt = len;
        }
        copy_n(r.ring.at(0), tgt, &buf[ret]);
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
        copy_n(&buf[0], len, r.ring.at(r.wp));
        ret = len;
        r.wp += len;
    }
    else {
        size_t tgt;
        size_t wp;

        ret = 0;
        tgt = r.ring.size() - r.wp;
        copy_n(&buf[0], tgt, r.ring.at(r.wp));
        ret = tgt;
        len -= tgt;
        wp = r.wp + tgt;

        tgt = r.rp - (r.wp % r.ring.size());
        if (tgt > len) {
            tgt = len;
        }
        copy_n(&buf[ret], tgt, r.ring.at(wp));
        ret += tgt;
        len -= tgt;
        r.wp = tgt;
    }

    return ret;
}
