all: AVL.o teste.o
	gcc AVL.o teste.o -o runabble -std=c99 -Wall

AVL.o:
	gcc -c AVL.c -o AVL.o

## teste
teste.o:
	gcc -c teste.c -o teste.o

run: all
	./runabble

clean:
	rm *.o runabble

test:
	clear
	make clean
	make all
	make run