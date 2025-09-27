CC = gcc
AS = nasm
LD = ld

CFLAGS = -m64 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -Iinclude/ -ffreestanding

ASFLAGS = -f elf64

C_SOURCES = $(wildcard src/*.c)
ASM_SOURCES = $(WILDCARD boot/*.asm)

C_OBJECTS = $(C_SOURCES:.c=.o)
ASM_OBJECTS = $(ASM_SOURCES:.asm=.o)

all: metal.bin

metal.bin: $(C_OBJECTS) $(ASM_OBJECTS)
	$(LD) -T linker.ld -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f src/*.o metal.bin

run: metal.bin
	qemu-system-x86_64 -enable-kvm -cpu host -m 512M -kernel metal.bin

debug: metal.bin
	qemu-system-x86_64 -enable-kvm -cpu host -m 512M -kernel metal.bin -s -S &
	gdb -ex "target remote localhost:1234" -ex "symbol-file metal.bin"

.PHONY: all clean run debug
