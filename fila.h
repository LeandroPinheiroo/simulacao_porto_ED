#ifndef _Fila_ 
#define _Fila_ 

typedef struct NAVIO{//Struct para simular navio
    int quantidade_conteiners;
    int id;
    int tempo;
}Navio;
typedef struct NODO{//Struct para celula
    //possui apontadores para o proximo valor e o anterior
    struct Nodo *proximo;
    //navio onde sera inserido valor
    Navio navio;
}Nodo;
typedef struct Fila{//Struct para fila
    int tamanho;
    Nodo *ultimo;
    Nodo *primeiro;
}Fila;

typedef int boolean;//insere um tipo boolean para facilitar retorno
//Cria escopo de funcoes
Fila* cria_fila();
boolean verifica_vazia_fila(Fila*);
boolean verifica_cheia_fila(Fila*);
boolean destroi_fila(Fila*);
void insere_fila(Fila*,Navio);
void remove_fila(Fila*,Navio*);
void mostra_fila(Fila*);


#endif
