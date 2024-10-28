/* SPDX-License-Identifier: BSD-1-Clause */
/*
 * Copyright 2024 nekosanteam <1688092+nekosanteam@users.noreply.github.com>. All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions
 *    and the following disclaimer.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS
 * AND CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef NKPERSISTENT_HPP_
#define NKPERSISTENT_HPP_
/**
 * @file nkpersistent.hpp
 */

#include <cstdint>

namespace nk {
namespace persistent {

static inline int popcount(uint32_t bits)
{

}

class ArrayBase {
public:
    std::uint32_t  bitmap_;
    std::uint32_t  next_;
    std::uintptr_t ptr_;
    ArrayBase*     base_;

public:
    ArrayBase(std::size_t size);
    
    void* at(std::size_t index) {
        if (index < 32) {
            if ((bitmap_ & (1 << index)) != 0) {
                return (void*)(((void**)ptr_)[popcount((bitmap_ & ((1 << index))))]);
            } else {
                return nullptr;
            }
        } else {
            if (next_ != 0) {
                for (std::size_t s=0; base_[s].next_ != 0; s++) {
                    if ((base_[s].next_ <= index) && (index < (base_[s].next_ + 32))) {
                        if ((base_[s].bitmap_ & (1 << (index - s))) != 0) {
                            return (void*)(((void**)base_[s].ptr_)[popcount(base_[s].bitmap_ & ((1 << (index - s))))]);
                        } else {
                            return nullptr;
                        }
                    }
                }
            } else {
                return nullptr;
            }
        }
    }
};

}
}

#endif /* NKPERSISTENT_HPP_ */
