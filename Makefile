# Makefile

all: os.img

os.img: boot.asm
	nasm -f bin boot.asm -o os.img

clean:
	rm -f os.img
