all:
	gcc -c A.c
	gcc A.o -o A
	gcc -c B.c -lpthread
	gcc B.o -o B -lpthread

clean:
	rm A B A.o B.o