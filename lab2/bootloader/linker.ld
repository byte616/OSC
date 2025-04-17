ENTRY(_start)

SECTIONS
{
  . = 0x60000; /* bootloader start address  */
  
  text_start = .;
  .text : { *(.text.boot) *(.text) }
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

}

