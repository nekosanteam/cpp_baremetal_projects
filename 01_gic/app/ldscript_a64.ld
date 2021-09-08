OUTPUT_ARCH(AArch64)
ENTRY(_start)
SECTIONS
{
    . = 0x80000;

    __text_start = .;
    .text : { *(.text*) }
    . = ALIGN(4);
    __text_end = .;

    __rodata_start = .;
    .rodata : { *(.data*) }
    . = ALIGN(4);
    __rodata_end = .;

    __data_start = .;
    .data : { *(.data*) }
    . = ALIGN(4);
    __data_end = .;

    __bss_start = .;
    .bss : { *(.bss*) }
    . = ALIGN(4);
    __bss_end = .;

    __stack_start = .;
    stack_top = .;
    . = . + 0x0800;
    . = . + 0x0800;
    . = . + 0x0800;
    . = . + 0x0800;
    . = ALIGN(8);
    __stack_end = .;
}
