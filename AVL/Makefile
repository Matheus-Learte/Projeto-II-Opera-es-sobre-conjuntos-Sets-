all: avl.o teste.o
	gcc avl.o teste.o -o pato -std=c99 -Wall

avl.o:
	gcc -c AVL.c -o avl.o

teste.o:
	gcc -c teste.c -o teste.o

clean:
	rm *.o pato

run:
	./pato
