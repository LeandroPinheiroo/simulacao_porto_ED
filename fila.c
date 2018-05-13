#include "fila.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

enum bool{false = 0,true};//Enum para facilitar retorno de verdadeiro e falso

Fila* cria_fila(){
    Fila *fila;//Cria ponteiro para fila
    fila = (Fila*) malloc(sizeof(Fila));//Aloca na memoria
    fila->ultimo = NULL;//ultimo elemento recebe null
    fila->primeiro = NULL;//primeiro elemento recebe null
    fila->tamanho = 0;
    return fila;//retorna a fila criada
}
boolean destroi_fila(Fila *fila){//destroi a fila 
    Navio *aux;//Declara variavel para receber retorno da funcao de remover da fila
    while(verifica_vazia_fila(fila) == false){//equanto fila nao esta vazia
        remove_fila(fila, aux);//remove o elemento
    }
    if(verifica_vazia_fila(fila) == true){//verifica novamente se esta vazia
        free(fila);//libera a fila
        return true;//retorna verdadeiro
    }
    return false;//retorna falso caso encontra algum erro
}

boolean verifica_vazia_fila(Fila *fila){
    if(fila->tamanho == 0){//se tamanho igual a 0 indica que fila esta vazia
        return true;//retorna verdadeiro
    }
    return false;//retorna falso indicando que nao esta cheia
}
void insere_fila(Fila *fila,Navio navio){
    if(verifica_vazia_fila(fila) == true){//verifica se esta vazia
        //se estiver vazia cria a primeira nodo
        fila->primeiro = (Nodo*)malloc(sizeof(Nodo));//aloca na ultima posicao
        fila->ultimo = fila->primeiro;//aloca na ultima posicao
        fila->ultimo->proximo = NULL;//aponta o proximo para vazio
        fila->tamanho = 1;//tamanho recebe 1
        fila->ultimo->navio.id = navio.id;//insere o id
        fila->ultimo->navio.tempo = navio.tempo;//insere o tempo
        fila->ultimo->navio.quantidade_conteiners = navio.quantidade_conteiners;//insere o elemento
        return;//sai da funcao
    }
    fila->ultimo->proximo = malloc(sizeof(Nodo));//aloca a proxima posicao
    fila->ultimo = (Nodo*)fila->ultimo->proximo;//ultimo recebe o proximo
    fila->ultimo->navio.id = navio.id;//insere o id
    fila->ultimo->navio.tempo = navio.tempo;//insere o tempo
    fila->ultimo->navio.quantidade_conteiners = navio.quantidade_conteiners;//insere o elemento
    fila->ultimo->proximo = NULL;//proximo ao ultimo aponta para null
    fila->tamanho++;//soma no contador de elementos
}

void remove_fila(Fila *fila, Navio *navio){
    Nodo *aux = NULL;//declara auxiliar para ajudar com o retorno
    if(verifica_vazia_fila(fila) == false){//verifica se a fila nao esta vazia
        if(fila->tamanho == 1){
            navio->id = fila->primeiro->navio.id;//navio recebe o valor
            navio->tempo = fila->primeiro->navio.tempo;//navio recebe o valor
            navio->quantidade_conteiners = fila->primeiro->navio.quantidade_conteiners;//navio recebe o valor
            free(fila->ultimo);//libera o proximo elemento
            fila->primeiro = NULL;//primeiro elemento aponta para null
            fila->ultimo = NULL;//ultimo elemento aponta para null
            fila->tamanho--;
            return;
        }
        aux = fila->primeiro;//primeiro elemento eh passado para o auxiliar
        fila->primeiro =(Nodo*)fila->primeiro->proximo; //primeiro elemento eh passado para o proximo a ele
        free(aux);//libera o primeiro que esta gravado no auxiliar
        fila->tamanho--;//subtrai no tamanho
    }
    navio->id = aux->navio.id;//navio recebe o valor
    navio->tempo = aux->navio.tempo;//navio recebe o valor
    navio->quantidade_conteiners = aux->navio.quantidade_conteiners;//navio recebe
}

/*
A funcao de mostrar elemento possivelmente nao sera utilizada porem foi criada para testes
*/
void mostra_fila(Fila *fila){
    int cont = 0;
    if(verifica_vazia_fila(fila) == false){
        Nodo *aux = fila->primeiro;
        while(aux != NULL){
            printf("Código = %d \t",aux->navio.id);
            printf("Conteiners = %d \t",aux->navio.quantidade_conteiners);
            printf("Tempo na fila = %d \t",aux->navio.tempo);
            aux = (Nodo*)aux->proximo;
            cont++;
            //iF que evita mostrar muitos navios na mesma linha
            if(cont == 2){
                cont = 0;
                printf("\n");
            }
        }
        printf("\n");
    }
}