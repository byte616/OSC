# tool chain
CC = aarch64-linux-gnu-gcc
LD = aarch64-linux-gnu-ld
OBJCOPY = aarch64-linux-gnu-objcopy

# build options
CFLAGS = -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only -g
DFLAG = -s -S
LINKER = kernel/linker.ld
BLINKER = bootloader/linker.ld

# output files
IMG = kernel8.img
ELF = kernel8.elf
BLIMG = bootloader.img
BLELF = bootloader.elf

# source files
SRC_C := $(shell find src/ -name "*.c")
SRC_S := $(shell find src/ -name "*.s")
OBJ := $(SRC_C:%.c=%.o) $(SRC_S:%.s=%.o) 

KER_C := $(shell find kernel/ -name "*.c")
KER_S := $(shell find kernel/ -name "*.s")
KOBJ := $(KER_C:%.c=%.o) $(KER_S:%.s=%.o)

BL_C := $(shell find bootloader/ -name "*.c")
BL_S := $(shell find bootloader/ -name "*.s")
BLOBJ := $(BL_C:%.c=%.o) $(BL_S:%.s=%.o) $(SRC_C:%.c=%.o)

all: $(IMG) $(BLIMG)

qemu: $(IMG)
	qemu-system-aarch64 -M raspi3b -kernel $< -serial null -serial stdio -display none

debug: $(BLIMG)
	qemu-system-aarch64 -M raspi3b -kernel $< -serial null -serial pty -serial pty -display none 

%.o: %.s
	$(CC) -o $@ -c $<

%.o: %.c
	$(CC) -o $@ $(CFLAGS) -c $<

# link to ELF
$(ELF): $(OBJ) $(KOBJ)
	$(LD) -T $(LINKER) -o $(ELF) $^
	
# ELF to image
$(IMG): $(ELF) 
	$(OBJCOPY) -O binary $(ELF) $@

# boot loader 
$(BLELF): $(BLOBJ)
	$(LD) -T $(BLINKER) -o $(BLELF) $^

$(BLIMG): $(BLELF)	
	$(OBJCOPY) -O binary $(BLELF)  $@

gen_cpio:
	mkdir -p rootfs
	echo "Hello World!" > rootfs/file1.txt
	echo "test 123" > rootfs/file2.txt
	cd rootfs && find * | cpio -o -H newc > ../initramfs.cpio
	cd ..

clean: 
	rm -f $(OBJ) $(ELF) $(IMG) $(KOBJ) $(BLOBJ) $(BLELF) $(BLIMG)

.PHONY: all clean QEMU

