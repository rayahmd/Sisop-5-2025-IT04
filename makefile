# Variabel
AS = nasm
CC = gcc
LD = ld
RM = rm -f
CFLAGS = -ffreestanding -Wall -nostdlib -m32 -g
LDFLAGS = -m elf_i386 -Ttext 0x1000

# Direktori
SRC_DIR = src
BIN_DIR = bin
INC_DIR = include

# File
BOOTLOADER_SRC = bootloader.asm
BOOTLOADER_OBJ = $(BIN_DIR)/bootloader.bin
STD_LIB_SRC = std_lib.c
STD_LIB_OBJ = $(BIN_DIR)/std_lib.o
SHELL_SRC = shell.c
SHELL_OBJ = $(BIN_DIR)/shell.o
KERNEL_SRC = kernel.c
KERNEL_OBJ = $(BIN_DIR)/kernel.o
KERNEL_ASM_SRC = kernel.asm
KERNEL_ASM_OBJ = $(BIN_DIR)/kernel_asm.o
OUTPUT_IMG = $(BIN_DIR)/floppy.img

# Target utama
all: build

# Persiapan
prepare:
	$(RM) $(OUTPUT_IMG)

# Kompilasi bootloader
bootloader: $(BOOTLOADER_OBJ)

$(BOOTLOADER_OBJ): $(SRC_DIR)/$(BOOTLOADER_SRC)
	$(AS) -f bin -o $@ $<

# Kompilasi std_lib
stdlib: $(STD_LIB_OBJ)

$(STD_LIB_OBJ): $(SRC_DIR)/$(STD_LIB_SRC)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Kompilasi shell
shell: $(SHELL_OBJ)

$(SHELL_OBJ): $(SRC_DIR)/$(SHELL_SRC)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Kompilasi kernel
kernel: $(KERNEL_OBJ) $(KERNEL_ASM_OBJ)

$(KERNEL_OBJ): $(SRC_DIR)/$(KERNEL_SRC)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(KERNEL_ASM_OBJ): $(SRC_DIR)/$(KERNEL_ASM_SRC)
	$(AS) -f elf -o $@ $<

# Link dan buat image
link: $(BOOTLOADER_OBJ) $(KERNEL_OBJ) $(KERNEL_ASM_OBJ) $(STD_LIB_OBJ) $(SHELL_OBJ)
	$(LD) $(LDFLAGS) -o $(BIN_DIR)/kernel.bin $^
	cat $(BIN_DIR)/bootloader.bin $(BIN_DIR)/kernel.bin > $(OUTPUT_IMG)

# Build semua target
build: prepare bootloader stdlib shell kernel link

