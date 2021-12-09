OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
        . = 0x00008000;

        .text : { *(.text*) }
        . = ALIGN(4);

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
        __stack_top = .;
        . += 0x0800;
        . += 0x0800;
        . += 0x0800;
        . += 0x0800;
        . = ALIGN(4);
        __stack_bottom = .;
        __stack_end = .;
}
