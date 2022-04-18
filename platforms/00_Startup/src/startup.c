
void clear_bss()
{
    extern const char __bss_start[];
    extern const char __bss_end[];

    unsigned int* p;
    unsigned int* start = (unsigned int*)&__bss_start[0];
    unsigned int* end   = (unsigned int*)&__bss_end[0];

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

_Unwind_Reason_Code
__gxx_personality_v0(int version, _Unwind_Action actions, uint64_t exceptionClass,
                     _Unwind_Exception* unwind_exception, _Unwind_Context* context)
{
    return 0;
}

void _Unwind_Resume(_Unwind_Exception *exception_object)
{
}

void __stack_chk_fail(void)
{
}
