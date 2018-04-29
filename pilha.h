#ifndef _Pilha_ 
#define _Pilha_ 

typedef struct CONTEINER{//Struct para simular conteiner
    int valor;
}Conteiner;
typedef struct CELULA{//Struct para celula
    //possui apontadores para o proximo valor e o anterior
    struct Celula *proximo;
    struct Celula *anterior;
    //conteiner onde sera inserido valor
    Conteiner conteiner;
}Celula;
typedef struct PILHA{//Struct para pilha
    //possui o tamanho da pilha o ultimo elemento que eh o topo da pilha
    int tamanho;
    Celula *ultimo;
}Pilha;

typedef int boolean;//insere um tipo boolean para facilitar retorno
//Cria escopo de funcoes
Pilha* cria_pilha();
boolean verifica_vazia_pilha(Pilha*);
boolean verifica_cheia_pilha(Pilha*);
boolean destroi_pilha(Pilha*);
void insere_pilha(Pilha*,Conteiner);
void remove_pilha(Pilha*,Conteiner*);
void mostra_pilha(Pilha*);
#endif
