//====================Leandro Souza Pinheiro====================
//====================0015137===================================
//====================Ciência da Computação=====================
//====================Trabalho de Estrutura de Dados============

#include "pilha.h"
#include "fila.h"
#include "desenvolvimento.h"
#include <time.h>
#include<unistd.h> 
#include "keyboard.h"//biblioteca do PARANÁ


enum bool{false = 0,true};//Enum para facilitar retorno de verdadeiro e falso

int main(){
    Fila *fila1; Fila *fila2; Fila *fila3; Fila *fila4;
    fila1 = cria_fila();
    fila2 = cria_fila();
    fila3 = cria_fila();
    fila4 = cria_fila();
    struct ATRACAMENTO atracamento[4];
    for(int i = 0;i<4;i++){
        atracamento[i].contador_veiculo = 0;
        for(int j = 0;j<5;j++){
            atracamento[i].travessa[j].pilha = cria_pilha();
            atracamento[i].travessa[j].pilha->tamanho = 0;
        }
    }
    int fila_insere = 1;
    srand(time(NULL));
    int quantidade_navio = 0;
    int c;
    //Cria pilhas dos navios    
    do{
        //NAVIO CHEGA NA FILA
        quantidade_navio = (rand() % 6);
        Navio navio_fila1,navio_fila2,navio_fila3,navio_fila4;
        if(quantidade_navio != 0){
            for(int i=0;i<quantidade_navio;i++){
                if(fila_insere == 4){
                    //Cria pilhas dos navios
                    //por conteiner na pilha primeiro e dps enfileirar
                    navio_fila4 = insere_navio_fila(fila4);
                    fila4->ultimo->navio.pilha1 = cria_pilha();
                    fila4->ultimo->navio.pilha2 = cria_pilha();
                    fila4->ultimo->navio.pilha3 = cria_pilha();
                    fila4->ultimo->navio.pilha4 = cria_pilha();
                    pilhas_navio(fila4->ultimo->navio);
                    fila_insere = 1;
                }
                else if(fila_insere == 3){
                    //Cria pilhas dos navios
                    navio_fila3 = insere_navio_fila(fila3);
                    fila3->ultimo->navio.pilha1 = cria_pilha();
                    fila3->ultimo->navio.pilha2 = cria_pilha();
                    fila3->ultimo->navio.pilha3 = cria_pilha();
                    fila3->ultimo->navio.pilha4 = cria_pilha();
                    pilhas_navio(fila3->ultimo->navio);
                    fila_insere = 4;
                }
                else if(fila_insere == 2){
                    //Cria pilhas dos navios
                    navio_fila2 = insere_navio_fila(fila2);
                    fila2->ultimo->navio.pilha1 = cria_pilha();
                    fila2->ultimo->navio.pilha2 = cria_pilha();
                    fila2->ultimo->navio.pilha3 = cria_pilha();
                    fila2->ultimo->navio.pilha4 = cria_pilha();
                    pilhas_navio(fila2->ultimo->navio);
                    fila_insere = 3;
                }
                else if(fila_insere == 1){
                    navio_fila1 = insere_navio_fila(fila1);
                    //Cria pilhas dos navios
                    fila1->ultimo->navio.pilha1 = cria_pilha();
                    fila1->ultimo->navio.pilha2 = cria_pilha();
                    fila1->ultimo->navio.pilha3 = cria_pilha();
                    fila1->ultimo->navio.pilha4 = cria_pilha();
                    pilhas_navio(fila1->ultimo->navio);
                    fila_insere = 2;
                }
            }
        }
        system("clear");//limpa terminal
        //RELATORIO ATUAL
        printf("\t\t==ATENÇÃO==\nPressione qualquer tecla para parar a execução\n\n");
        printf("==========RELATORIO==========\n");
        
        if(quantidade_navio > 1){
            printf("\nChegaram %d novos navios ao porto\n", quantidade_navio);
            printf("Esses navios foram inseridos na fila e vão esperar sua vez para atracar\n\n");
        }else if(quantidade_navio == 1){
            printf("\nChegou %d novo navio ao porto\n", quantidade_navio);
            printf("Esse navio foi inserido na fila e vai esperar sua vez para atracar\n\n");
        }else{
            printf("\nNão chegou nenhum novo navio no porto\n\n");
        }
        if(verifica_vazia_fila(fila1) == false){
            printf("==ID's dos navios da fila 1==\n");
            mostra_fila(fila1);//Navios na fila 1
        }
        if(verifica_vazia_fila(fila2) == false){
            printf("==ID's dos navios da fila 2==\n");
            mostra_fila(fila2);//Navios na fila 2
        }  
        if(verifica_vazia_fila(fila3) == false){
            printf("==ID's dos navios da fila 3==\n");
            mostra_fila(fila3);//Navios na fila 3
        }         
        if(verifica_vazia_fila(fila4) == false){
            printf("==ID's dos navios da fila 4==\n");
            mostra_fila(fila4);//Navios na fila 2
        }
        printf("\n");
        for(int i = 0;i<4;i++){
           for(int j = 0;j<5;j++){
                if(j != 2){
                    printf("\t\t\t Travessa = %d Tamanho = %d\n",j,atracamento[i].travessa[j].pilha->tamanho);
                }else if(j == 2){
                    printf("Atracamento = %d \t Travessa = %d Tamanho = %d \t Veiculo foi utilizado = %d vezes\n",i,j,atracamento[i].travessa[j].pilha->tamanho,atracamento[i].contador_veiculo);
                }
           }
           printf("\n");
        }
        //CHAMA VEICULO DE TRANSPORTE caso seja necessario
        for(int i = 0;i<4;i++){
           for(int j = 0;j<5;j++){
               if(atracamento[i].travessa[j].pilha->tamanho == 5){
                   chama_veiculo_transporte(atracamento[i].travessa[j]);
                   atracamento[i].contador_veiculo++;//Aumenta no contador do veiculo dessa travessa
                   j = 5;//Veiculo do atracamento foi usado e so podera ser usado da proxima vez
               }
            }
        }
        //DESCARREGA NAVIO da FILA 1
        if(verifica_vazia_fila(fila1) == false){
            incrementa_tempo_fila(fila1);//incrementa no tempo que o navio esta parado na fila
            descarrega_navio(atracamento, fila1);
        }
        //Descarrega navio da fila 2
        if(verifica_vazia_fila(fila2) == false){
            incrementa_tempo_fila(fila2);//incrementa no tempo que o navio esta parado na fila
            descarrega_navio(atracamento, fila2);
        }
        //Descarrega navio da fila 3
        if(verifica_vazia_fila(fila3) == false){
            incrementa_tempo_fila(fila3);//incrementa no tempo que o navio esta parado na fila
            descarrega_navio(atracamento, fila3);
        }//Descarrega navio da fila 4
        if(verifica_vazia_fila(fila4) == false){
            incrementa_tempo_fila(fila4);//incrementa no tempo que o navio esta parado na fila
            descarrega_navio(atracamento, fila4);
        }
        sleep(5);
        
    }while(!keyboard_pressed());//Repete ate usuario pressionar uma tecla, biblioteca cedida pelo PARANÁ
    printf("\n====================Relatório Final====================\n");
    printf("Caso algum navio tenha ficado na fila sem atracar será mostrado a seguir \n");
    if(verifica_vazia_fila(fila1) == false){
            printf("==ID's dos navios da fila 1==\n");
            mostra_fila(fila1);//Navios na fila 1
    }
    if(verifica_vazia_fila(fila2) == false){
        printf("==ID's dos navios da fila 2==\n");
        mostra_fila(fila2);//Navios na fila 2
    }  
    if(verifica_vazia_fila(fila3) == false){
        printf("==ID's dos navios da fila 3==\n");
        mostra_fila(fila3);//Navios na fila 3
    }         
    if(verifica_vazia_fila(fila4) == false){
        printf("==ID's dos navios da fila 4==\n");
        mostra_fila(fila4);//Navios na fila 2
    }
    return 0;
}
