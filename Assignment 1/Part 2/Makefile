all:
	nasm -f elf64 B.asm -o B.o
	gcc A.c B.o -o A -no-pie

clean:
	rm A B.o