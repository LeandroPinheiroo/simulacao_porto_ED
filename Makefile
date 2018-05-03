main:	main.o	fila.o	pilha.o	desenvolvimento.o	keyboard.o
	gcc main.o fila.o pilha.o desenvolvimento.o keyboard.o -o exe
	rm *.o 

main.o:	main.c
	gcc -c main.c

fila.o:	fila.c	fila.h
	gcc -c fila.c

pilha.o:	pilha.c	pilha.h
	gcc -c pilha.c

desenvolvimento.o:	desenvolvimento.c	desenvolvimento.h
	gcc -c desenvolvimento.c

keyboard.o:	keyboard.c	keyboard.h
	gcc -c keyboard.c

	
	