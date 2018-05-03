#ifndef _Desenvolvimento_ 
#define _Desenvolvimento_ 
#include "pilha.h"
#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 

struct TRAVESSA{
    Pilha *pilha;
}Travessa;
struct ATRACAMENTO{
    struct TRAVESSA travessa[5];
    int contador_veiculo;
}Atracamento;

void salva_id_txt(int id);
int gera_id_navio();
Navio gera_navio();
Conteiner gera_conteiner();
void pilhas_navio(Navio navio);
Navio insere_navio_fila(Fila *fila);
void chama_veiculo_transporte(struct TRAVESSA travessa);
boolean verifica_navio_descarregou(Navio navio);
void descarrega_navio(struct ATRACAMENTO atracamento[], Fila *fila);
#endif
