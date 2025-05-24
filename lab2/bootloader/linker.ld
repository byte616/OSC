ENTRY(_relocation)

_kernel_start = 0x80000;
_loader_start = 0x60000;
stack_size = 0x8000;
heap_size = 0x8000;

SECTIONS
{
  . = _loader_start; /* bootloader start address  */
  
  text_start = .;
  .text : { *(.text.relocation) *(.text.boot) *(.text) }
  . = ALIGN(0x10);
  text_end = .;

  rodata_start = .;
  .rodata : { *(.rodata) }
  . = ALIGN(0x10);
  rodata_end = .;

  data_begin = .;
  .data : { *(.data) }
  . = ALIGN(0x10);
  data_end = .;

  bss_begin = .; 
  .bss : { *(.bss*) }
  . = ALIGN(0x10);
  bss_end = .;

  . = bss_end + heap_size;

  _stack_top = . + stack_size;
  . = _stack_top;
  PROVIDE(code_size = . - _loader_start);
}

