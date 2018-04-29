#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "fila.h"


int main(){
    Fila *fila = cria_fila();
    Navio navio;
    navio.id = 90;
    insere_fila(fila,navio);
    navio.id = 50;
    insere_fila(fila,navio);
    navio.id = 700;
    insere_fila(fila,navio);
    navio.id = 1000;
    insere_fila(fila,navio);
    navio.id = 50000000;
    insere_fila(fila,navio);
    mostra_fila(fila);
    remove_fila(fila,&navio);
    printf("PRINT NA MAO 1 = %d\n",navio.id);
    remove_fila(fila,&navio);
    printf("PRINT NA MAO 2 = %d\n",navio.id);
    mostra_fila(fila);

    remove_fila(fila,&navio);
    printf("PRINT NA MAO 3 = %d\n",navio.id);
    boolean bo = destroi_fila(fila);
    if(bo == 1){
        printf("TRUE");
    }



    return 0;
}