/* SPDX-License-Identifier: BSD-1-Clause */
/*
 * Copyright 2023,2024 nekosanteam <1688092+nekosanteam@users.noreply.github.com>. All Rights Reserved.
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

void clear_bss()
{
    extern const char __bss_start[];
//    extern const char __end[];

    unsigned int* p;
    unsigned int* start = (unsigned int*)&__bss_start[0];
 //   unsigned int* end   = (unsigned int*)&__end[0];
    unsigned int* end = 0;

    for (p = start; p < end; p++) {
        *p = 0;
    }
}

typedef int _Unwind_Reason_Code;
typedef int _Unwind_Action;
typedef unsigned long uint32_t;
typedef unsigned long long uint64_t;
typedef struct {
    uint32_t reserved0;
    uint32_t reserved1;
    uint32_t reserved2;
    uint32_t reserved3;
} _Unwind_Exception;

typedef struct {
    uint32_t reserved0;
    uint32_t reserved1;
    uint32_t reserved2;
    uint32_t reserved3;
} _Unwind_Context;

#define NOT_USED(v) do { (void)(v); } while(0)

_Unwind_Reason_Code
__gxx_personality_v0(int version, _Unwind_Action actions, uint64_t exceptionClass,
                     _Unwind_Exception* unwind_exception, _Unwind_Context* context)
{
    NOT_USED(version);
    NOT_USED(actions);
    NOT_USED(exceptionClass);
    NOT_USED(unwind_exception);
    NOT_USED(context);
    return 0;
}

void _Unwind_Resume(_Unwind_Exception *exception_object)
{
    NOT_USED(exception_object);
}

void __stack_chk_fail(void)
{
}
