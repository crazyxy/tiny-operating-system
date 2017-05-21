# Automatically expand to a list of existing files that
# match the patterns
C_SOURCES = $(wildcard kernel/*.c drivers/*.c)

# Create a list of object files to build, simple by replacing
# the '.c' extension of filenames in C_SOURCES with '.o'
OBJ = $(C_SOURCES:.c=.o)



# $@ = target file
# $< = first dependency
# $^ = all dependencies


all: os-image

run: os-image
	qemu-system-i386 -fda os-image

os-image: boot/boot_sect.bin kernel.bin
	cat $^ > os-image

kernel.bin: kernel/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

%.o: %.c ${HEADERS}
	i386-elf-gcc -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -I 'boot/' -o $@

clean:
	rm -rf *.bin *.o *.dis os-image
	rm -rf kernel/*.o boot/*.bin

kernel.dis: kernel.bin
	ndisasm -b 32 $< >$@
