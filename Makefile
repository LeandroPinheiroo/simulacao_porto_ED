main:	main.o	fila.o	pilha.o
	gcc main.o fila.o pilha.o '-lncurses' -o exe
	rm *.o 

main.o:	main.c
	gcc -c main.c

fila.o:	fila.c	fila.h
	gcc -c fila.c

pilha.o:	pilha.c	pilha.h
	gcc -c pilha.c
	