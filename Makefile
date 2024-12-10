all: AVL.o LLRBT.o SET.o main.o
	gcc AVL.o LLRBT.o SET.o main.o -o papai -std=c99 -Wall

AVL.o:
	gcc -c AVL.c -o AVL.o

LLRBT.o:
	gcc -c LLRBT.c -o LLRBT.o

SET.o:
	gcc -c SET.c -o SET.o

main.o:
	gcc -c main.c -o main.o

run:
	./papai

clean: 
	rm *o papai