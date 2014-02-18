bootblock: start.S main.c asm.h boot.h
	gcc -c -m32 start.S
	gcc -c -m32 -O1 main.c
	ld -melf_i386 -e start -Ttext 0x7C00 start.o main.o -o bootblock.o
	@objcopy -S -O binary -j .text bootblock.o bootblock
	@perl ./genboot.pl bootblock

clean:
	rm -rf bootblock *.o
