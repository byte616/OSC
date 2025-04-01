.section ".text.boot"
.globl _start

_start:
	mrs x0, mpidr_el1 // get process ID from mpidr_el1 reg
	and x0, x0, #0xFF // x0, has many info, get last 8 bits --> core ID
	cbz x0, primary // if x0 == 0, jump to primary

non_primary:
	wfe
	b non_primary // other core, take a break

primary:
	ldr x0, bss_begin
	ldr x1, bss_end
	sub x1, x1, x0 // end - begin = size of bss
	bl memzero

	mov sp, #0x40000 // set stack pointer
	bl main

memzero:
	cbnz x1, clean_bss // x1 != 0, clean bss
	ret

clean_bss:
	str xzr, [x0], #8 // xzr is special reg store 0, store 0 in to address x0 point to, x0 += 8 bytes
	sub x1, x1, #8 // decrease 8 bytes, until x1 = 0 --> bss all clear
	cbnz x1, clean_bss // x1 != 0, keep going
	ret




