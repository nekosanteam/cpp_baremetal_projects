void clear_bss()
{
    extern void* __bss_start;
    extern void* __bss_end;

    unsigned int* p;
    unsigned int* start = (unsigned char*)__bss_start;
    unsigned int* end   = (unsigned char*)__bss_end;

    for (p = start; p < end; p++) {
        *p = 0;
    }
}
