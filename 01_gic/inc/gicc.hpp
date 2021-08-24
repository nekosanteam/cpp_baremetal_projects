#pragma once 

#include <cstddef>
#include <cstdint>

namespace work {
class GICD {
public:
    GICD() {
    }
    ~GICD() {
    }

    void init();
    void enable(int intno);
    void disable(int intno);
};

class GICC {
public:
    GICC() {
    }
    ~GICC() {
    }

    void init();
    void enable();
    void disable();
};

} // namespace work
