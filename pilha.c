#include "pilha.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

enum bool{false = 0,true};//Enum para facilitar retorno de verdadeiro e falso

Pilha* cria_pilha(){
    Pilha *pilha;//Cria ponteiro para pilha
    pilha = (Pilha*) malloc(sizeof(Pilha));//Aloca na memoria
    pilha->ultimo = NULL;//ultimo elemento recebe null
    pilha->tamanho = 0;//Zera o Tamanho da pilha
    return pilha;//retorna a pilha criada
}

boolean destroi_pilha(Pilha *pilha){//detroi a pilha
    Conteiner *aux;//Declara variavel para receber retorno da funcao de remover da pilha
    while(verifica_vazia_pilha(pilha) == false){//equanto pilha nao esta vazia
        remove_pilha(pilha, aux);//remove o elemento
    }
    if(verifica_vazia_pilha(pilha) == true){//verifica novamente se esta vazia
        free(pilha);//libera a pilha
        return true;//retorna verdadeiro
    }
    return false;//retorna falso caso encontra algum erro
}


boolean verifica_vazia_pilha(Pilha *pilha){
    if(pilha->tamanho == 0){//se tamanho igual a 0 indica que pilha esta vazia
        return true;//retorna verdadeiro
    }
    return false;//retorna falso indicando que nao esta cheia
}

void insere_pilha(Pilha *pilha,Conteiner conteiner){
    if(verifica_vazia_pilha(pilha) == true){//verifica se esta vazia
        //se estiver vazia cria a primeira celula
        pilha->ultimo = (Celula*)malloc(sizeof(Celula));//aloca na ultima posicao
        pilha->ultimo->proximo = NULL;//aponta o proximo para vazio
        pilha->ultimo->anterior = NULL;//aponta o anterior para vazio
        pilha->tamanho = 1;//tamanho recebe 1
        pilha->ultimo->conteiner.valor = conteiner.valor;//insere o elemento
        return;//sai da funcao
    }
    Celula *aux;//cria celula auxiliar para ajudar no empilhamento
    pilha->ultimo->proximo = malloc(sizeof(Celula));//aloca a proxima posicao
    aux = (Celula*)pilha->ultimo;//auxiliar recebe o ultimo elemento
    pilha->ultimo = (Celula*)pilha->ultimo->proximo;//ultimo recebe o proximo
    pilha->ultimo->anterior = (Celula*)(aux);//o anterior ao ultimo recebe o auxiliar
    pilha->ultimo->conteiner.valor = conteiner.valor;//insere o elemento no ultimo
    pilha->ultimo->proximo = NULL;//proximo ao ultimo aponta para null
    pilha->tamanho++;//soma no contador de elementos
}
void remove_pilha(Pilha *pilha, Conteiner *conteiner){
    Celula *aux = NULL;//declara auxiliar para ajudar com o retorno
    if(verifica_vazia_pilha(pilha) == false){//verifica se a pilha nao esta vazia
        if(pilha->tamanho == 1){//verifica se so possui um elemento na pilha
            aux = pilha->ultimo;//ultimo elemento eh passado para auxiliar
            free(pilha->ultimo);//libera a posicao do ultimo
            pilha->ultimo = NULL;//ultimo elemento aponta para null
            pilha->tamanho = 0;//decrementa no tamanho da pilha
            conteiner->valor = aux->conteiner.valor;//passa o valor do auxiliar para o conteiner
            return;//sai da funcao
        }
        aux = pilha->ultimo;//utimo elemento eh passado para o auxiliar
        pilha->ultimo = (Celula*)pilha->ultimo->anterior;//o ultimo elemento volta para o anterior
        free(pilha->ultimo->proximo);//libera o proximo elemento
        pilha->ultimo->proximo = NULL;//o proximo elemento eh apontado para null
        pilha->tamanho--;//subtrai no tamanho
    }
    conteiner->valor = aux->conteiner.valor;//conteiner recebe o valor
}
/*
A funcao de mostrar elemento possivelmente nao sera utilizada porem foi criada para testes
*/
void mostra_pilha(Pilha *pilha){
    if(verifica_vazia_pilha(pilha) == false){
        Celula *aux = pilha->ultimo;
        while(aux != NULL){
            printf("%d\n",aux->conteiner.valor);
            aux = (Celula*)aux->anterior;
        }
    }
}