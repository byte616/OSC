# tool chain
CC = aarch64-linux-gnu-gcc
LD = aarch64-linux-gnu-ld
OBJCOPY = aarch64-linux-gnu-objcopy

# build options
CFLAGS = -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only -g
LINKER = linker.ld

# output files
IMG = kernel8.img
ELF = kernel8.elf

# source files
ALL_C := $(shell find . -name "*.c")
ALL_S := $(shell find . -name "*.s")
OBJ := $(ALL_C:%.c=%.o) $(ALL_S:%.s=%.o) 


all: $(IMG)

qemu: $(IMG)
	qemu-system-aarch64 -M raspi3b -kernel $< -serial null -serial stdio -display none

%.o: %.s
	$(CC) -o $@ -c $<

%.o: %.c
	$(CC) -o $@ $(CFLAGS) -c $<

# link to ELF
$(ELF): $(OBJ)
	$(LD) -T $(LINKER) -o $(ELF) $^
	
# ELF to image
$(IMG): $(ELF)
	$(OBJCOPY) -O binary $(ELF) $@

clean: 
	rm -f $(OBJ) $(ELF) $(IMG)

.PHONY: all clean QEMU

