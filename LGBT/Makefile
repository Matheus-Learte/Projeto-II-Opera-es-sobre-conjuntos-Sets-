all: llrbt.o teste.o
	gcc llrbt.o teste.o -o peixe -std=c99 -Wall

llrbt.o:
	gcc -c LLRBT.c -o llrbt.o

teste.o:
	gcc -c teste.c -o teste.o

clean:
	rm *.o peixe

run:
	./peixe
