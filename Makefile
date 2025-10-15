KERNEL_OBJS = \
    kernel/boot_header.o \
    kernel/main.o \
    kernel/shell.o \
    kernel/io.o \
    kernel/fs.o \
    kernel/string.o \
    kernel/keyboard.o \
    kernel/idt.o

INCLUDES = -Iinclude

all: os.iso

# Assembly
kernel/boot_header.o: kernel/boot_header.asm
	nasm -f elf32 kernel/boot_header.asm -o kernel/boot_header.o

kernel/keyboard.o: kernel/keyboard.asm
	nasm -f elf32 kernel/keyboard.asm -o kernel/keyboard.o

kernel/idt.o: kernel/idt.asm
	nasm -f elf32 kernel/idt.asm -o kernel/idt.o

# C Files
kernel/main.o: kernel/main.c
	gcc -m32 -ffreestanding -c kernel/main.c -o kernel/main.o $(INCLUDES)

kernel/shell.o: kernel/shell.c
	gcc -m32 -ffreestanding -c kernel/shell.c -o kernel/shell.o $(INCLUDES)

kernel/io.o: kernel/io.c
	gcc -m32 -ffreestanding -c kernel/io.c -o kernel/io.o $(INCLUDES)

kernel/fs.o: kernel/fs.c
	gcc -m32 -ffreestanding -c kernel/fs.c -o kernel/fs.o $(INCLUDES)

kernel/string.o: kernel/string.c
	gcc -m32 -ffreestanding -c kernel/string.c -o kernel/string.o $(INCLUDES)

# Link everything into the final kernel binary
kernel.bin: $(KERNEL_OBJS)
	ld -m elf_i386 -Ttext 0x100000 -o kernel.bin $(KERNEL_OBJS) --oformat binary

# Create bootable ISO
os.iso: kernel.bin
	mkdir -p isodir/boot/grub
	cp kernel.bin isodir/boot/kernel.bin
	echo 'set timeout=0' > isodir/boot/grub/grub.cfg
	echo 'set default=0' >> isodir/boot/grub/grub.cfg
	echo 'menuentry "CustomOS" {' >> isodir/boot/grub/grub.cfg
	echo '  multiboot /boot/kernel.bin' >> isodir/boot/grub/grub.cfg
	echo '  boot' >> isodir/boot/grub/grub.cfg
	echo '}' >> isodir/boot/grub/grub.cfg
	grub2-mkrescue -o os.iso isodir

# Cleanup
clean:
	rm -rf *.o *.bin *.iso isodir

