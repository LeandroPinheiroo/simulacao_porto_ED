main:	main.o	fila.o	pilha.o	desenvolvimento.o
	gcc main.o fila.o pilha.o desenvolvimento.o -o exe
	rm *.o 

main.o:	main.c
	gcc -c main.c

fila.o:	fila.c	fila.h
	gcc -c fila.c

pilha.o:	pilha.c	pilha.h
	gcc -c pilha.c

desenvolvimento.o:	desenvolvimento.c	desenvolvimento.h
	gcc -c desenvolvimento.c
	
	