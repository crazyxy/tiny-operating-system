# Automatically expand to a list of existing files that
# match the patterns
C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/.h)


# Create a list of object files to build, simple by replacing
# the '.c' extension of filenames in C_SOURCES with '.o'
OBJ = $(C_SOURCES:.c=.o)

CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
GDB = /usr/local/i386elfgcc/bin/i386-elf-gdb

CFLAGS = -g


# $@ = target file
# $< = first dependency
# $^ = all dependencies


all: os-image

run: os-image
	qemu-system-i386 -fda os-image

os-image: boot/boot_sect.bin kernel.bin
	cat $^ > os-image

kernel.bin: boot/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: boot/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^

debug: os-image kernel.elf
	qemu-system-i386 -s -fda os-image &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -I 'boot/' -o $@

clean:
	rm -rf *.bin *.o *.dis *.elf os-image
	rm -rf kernel/*.o boot/*.bin boot/*.o

kernel.dis: kernel.bin
	ndisasm -b 32 $< >$@
