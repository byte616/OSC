SECTIONS
{
  . = 0x80000; /* start address  */
  .text : { *(.text.boot) *(.text) }
  .rodata : { *(.rodata) }
  .data : { *(.data) }
  . = ALIGN(0x8); /* align bss*/
  bss_begin = .; /* record bss start pos */
  .bss : { *(.bss*) } 
  bss_end = .;
}
