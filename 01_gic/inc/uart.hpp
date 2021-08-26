#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

namespace work {

class UART {
public:
    UART();
    virtual ~UART();
    virtual void init() = 0;
    virtual int get() = 0;
    virtual void put(int ch) = 0;

    virtual int gets();
    virtual int sets();
};

} // namespace work
