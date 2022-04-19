OUTPUT_FORMAT("elf64-littleaarch64")
OUTPUT_ARCH(aarch64)
ENTRY(_start)
SECTIONS
{
	. = 0x40000000;

	__text_start = .;
	.text : { 
		*(.text*)
	}
	. = ALIGN(4);
	__text_end = .;

	__rodata_start = .;
	.rodata : { *(.data*) }
	. = ALIGN(4);
	__rodata_end = .;

	__init_array_start = .;
	.init.array : {
		*(.init.array)
		*(.init.array.*)
	}
	. = ALIGN(4);
	__init_array_end = .;

	__data_start = .;
	.data : { *(.data .data.*) }
	. = ALIGN(4);
	__data_end = .;

	__bss_start = .;
	.bss : { *(.bss .bss.*) }
	. = ALIGN(4);
	__bss_end = .;
	__end = .;

	__stack_start = .;
	__stack_top = .;
	. = . + 0x0800;
	. = . + 0x0800;
	. = . + 0x0800;
	. = . + 0x0800;
	. = ALIGN(8);
	__stack_bottom = .;
	__stack_end = .;
}