void clear_bss()
{
    extern void* __bss_start;
    extern void* __bss_end;

    unsigned char* p;
    unsigned char* start = (unsigned char*)&__bss_start;
    unsigned char* end   = (unsigned char*)&__bss_end;

    for (p = start; p < end; p++) {
        *p = 0;
    }
}
