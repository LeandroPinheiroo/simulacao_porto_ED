#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include "fila.h"
#include "time.h"
#include <ncurses.h>

struct TRAVESSA{
    Pilha *pilha;
}Travessa;
struct ATRACAMENTO{
    struct TRAVESSA travessa[5];
}Atracamento;

void salva_id_txt(int id){
    FILE *arquivo;
    arquivo = fopen("navio.txt","a+");
    fprintf(arquivo,"%d;",id);
    fclose(arquivo);
}
int gera_id_navio(){
    FILE *arquivo;
    arquivo = fopen("navio.txt","r");
    int ultimo_id = 0;
    while(!feof(arquivo)){
        fscanf(arquivo,"%d",&ultimo_id);
        getc(arquivo);
        if(feof(arquivo)){
            break;
        }
    }
    ultimo_id++;
    salva_id_txt(ultimo_id);
    return ultimo_id;
}

Navio gera_navio(){
    Navio navio;
    srand(time(NULL));
    navio.id = gera_id_navio();
    navio.quantidade_conteiners = (rand() % 12) + 4;
    return navio;
}
Conteiner gera_conteiner(){
    Conteiner conteiner;
    conteiner.valor = 1;
    return conteiner;
}

void pilhas_navio(Navio navio){
    int pilha_atual = 1; 
    for(int i = 0;i<navio.quantidade_conteiners;i++){
        if(pilha_atual == 4){
            Conteiner conteiner = gera_conteiner();
            insere_pilha(navio.pilha4,conteiner);
            pilha_atual = 1;
        }
        else if(pilha_atual == 3){
            Conteiner conteiner = gera_conteiner();
            insere_pilha(navio.pilha3,conteiner);
            pilha_atual = 4;
        }
        else if(pilha_atual == 2){
            Conteiner conteiner = gera_conteiner();
            insere_pilha(navio.pilha2,conteiner);
            pilha_atual = 3;
        }
        else if(pilha_atual == 1){
            Conteiner conteiner = gera_conteiner();
            insere_pilha(navio.pilha1,conteiner);
            pilha_atual = 2;
        }
    }
}
Navio insere_navio_fila(Fila *fila){
    Navio navio = gera_navio();
    insere_fila(fila,navio);
    return navio;
}
void chama_veiculo_transporte(struct TRAVESSA travessa){
    for(int i = 0;i<5;i++){
        remove_pilha(travessa.pilha,&travessa.pilha->ultimo->conteiner);
    }
    travessa.pilha->tamanho = 0;
}
boolean verifica_navio_descarregou(Navio navio){
    if(navio.pilha1->tamanho == 0 && navio.pilha2->tamanho == 0 && navio.pilha3->tamanho == 0 && navio.pilha4->tamanho == 0){
        return true;
    }else{
        return false;
    }
}

int main(){
    Fila *fila1; Fila *fila2; Fila *fila3; Fila *fila4;
    fila1 = cria_fila();
    fila2 = cria_fila();
    fila3 = cria_fila();
    fila4 = cria_fila();
    struct ATRACAMENTO atracamento[4];
    for(int i = 0;i<4;i++){
        for(int j = 0;j<5;j++){
            atracamento[i].travessa[j].pilha = cria_pilha();
            atracamento[i].travessa[j].pilha->tamanho = 0;
        }
    }

    int fila_insere = 1;
    srand(time(NULL));
    int quantidade_navio = 0;
    int c;
    initscr();
    

    //Antes de iniciar coloca 4 navios nas filas para evitar erros  
    //Cria pilhas dos navios
    
    do{
        //NAVIO CHEGA NA FILA
        quantidade_navio =  (rand() % 4);
        printf("Quantidade navio = %d\n", quantidade_navio);
        Navio navio_fila1,navio_fila2,navio_fila3,navio_fila4;
        for(int i=0;i<quantidade_navio;i++){
            if(fila_insere == 4){
                //Cria pilhas dos navios
                navio_fila4 = insere_navio_fila(fila4);
                navio_fila4.pilha1 = cria_pilha();
                navio_fila4.pilha2 = cria_pilha();
                navio_fila4.pilha3 = cria_pilha();
                navio_fila4.pilha4 = cria_pilha();
                pilhas_navio(navio_fila4);
                fila_insere = 1;
            }
            else if(fila_insere == 3){
                //Cria pilhas dos navios
                navio_fila3 = insere_navio_fila(fila3);
                navio_fila3.pilha1 = cria_pilha();
                navio_fila3.pilha2 = cria_pilha();
                navio_fila3.pilha3 = cria_pilha();
                navio_fila3.pilha4 = cria_pilha();
                pilhas_navio(navio_fila3);
                fila_insere = 4;
            }
            else if(fila_insere == 2){
                //Cria pilhas dos navios
                navio_fila2 = insere_navio_fila(fila2);
                navio_fila2.pilha1 = cria_pilha();
                navio_fila2.pilha2 = cria_pilha();
                navio_fila2.pilha3 = cria_pilha();
                navio_fila2.pilha4 = cria_pilha();
                pilhas_navio(navio_fila2);
                fila_insere = 3;
            }
            else if(fila_insere == 1){
                navio_fila1 = insere_navio_fila(fila1);
                //Cria pilhas dos navios
                navio_fila1.pilha1 = cria_pilha();
                navio_fila1.pilha2 = cria_pilha();
                navio_fila1.pilha3 = cria_pilha();
                navio_fila1.pilha4 = cria_pilha();
                pilhas_navio(navio_fila1);
                fila_insere = 2;
            }
        }
        //CHAMA VEICULO DE TRANSPORTE caso seja necessario
        for(int i = 0;i<4;i++){
           for(int j = 0;j<5;j++){
               if(atracamento[i].travessa[j].pilha->tamanho == 5){
                   chama_veiculo_transporte(atracamento[i].travessa[j]);
                   j = 5;//Veiculo do atracamento foi usado e so podera ser usado da proxima vez
               }
            }
        }
        //DESCARREGA NAVIO da FILA 1
        Navio navio_descarregando;
        navio_descarregando = fila1->primeiro->navio;

        int nao_existe_travessa_livre = false;
        for(int contpilha = 0;contpilha<4;contpilha++){//Escolhe PILHA DO NAVIOs
            if(contpilha == 0){//caso pilha 1
                while(navio_descarregando.pilha1->tamanho != 0 && nao_existe_travessa_livre == false){//enquanto pilha nao acaba
                    for(int i = 0;i<4;i++){//Escolhe atracamento
                        for(int j = 0;j<5;j++){//pega travessa
                            if(i == 3 && j == 4){
                                nao_existe_travessa_livre = true;
                                contpilha = 4;
                            }
                            while(atracamento[i].travessa[j].pilha->tamanho < 5 && navio_descarregando.pilha1->tamanho != 0){
                                insere_pilha(atracamento[i].travessa[j].pilha,navio_descarregando.pilha1->ultimo->conteiner);
                                remove_pilha(navio_descarregando.pilha1, &navio_descarregando.pilha1->ultimo->conteiner);
                                if(navio_descarregando.pilha1->tamanho == 0){
                                    //Sai do for de procura por travessa
                                    j = 5;
                                    i = 4;
                                }
                            }
                        }
                    }
                }
            }else if(contpilha==1){
                nao_existe_travessa_livre = false;
                while(navio_descarregando.pilha2->tamanho != 0 && nao_existe_travessa_livre == false){//enquanto pilha nao acaba
                    for(int i = 0;i<4;i++){//Escolhe atracamento
                        for(int j = 0;j<5;j++){//pega travessa
                            if(i == 3 && j == 4){
                                nao_existe_travessa_livre = true;
                                contpilha = 4;
                            }
                            if(atracamento[i].travessa[j].pilha->tamanho < 5){
                                insere_pilha(atracamento[i].travessa[j].pilha,navio_descarregando.pilha2->ultimo->conteiner);
                                remove_pilha(navio_descarregando.pilha2, &navio_descarregando.pilha2->ultimo->conteiner);
                                if(navio_descarregando.pilha2->tamanho == 0){
                                    //Sai do for de procura por travessa
                                    j = 5;
                                    i = 4;
                                }
                            }
                        }
                    }
                }
            }else if(contpilha == 2){//Caso pilha 3
                nao_existe_travessa_livre = false;
                while(navio_descarregando.pilha3->tamanho != 0 && nao_existe_travessa_livre == false){//enquanto pilha nao acaba
                    for(int i = 0;i<4;i++){//Escolhe atracamento
                        for(int j = 0;j<5;j++){//pega travessa
                            if(i == 3 && j == 4){
                                nao_existe_travessa_livre = true;
                                contpilha = 4;
                            }
                            if(atracamento[i].travessa[j].pilha->tamanho < 5){
                                insere_pilha(atracamento[i].travessa[j].pilha,navio_descarregando.pilha3->ultimo->conteiner);
                                remove_pilha(navio_descarregando.pilha3, &navio_descarregando.pilha3->ultimo->conteiner);
                                if(navio_descarregando.pilha3->tamanho == 0){
                                    //Sai do for de procura por travessa
                                    j = 5;
                                    i = 4;
                                }
                            }
                        }
                    }
                }
            }else if(contpilha == 3){//caso pilha 4
                nao_existe_travessa_livre = false;
                while(navio_descarregando.pilha3->tamanho != 0 && nao_existe_travessa_livre == false){//enquanto pilha nao acaba
                    for(int i = 0;i<4;i++){//Escolhe atracamento
                        for(int j = 0;j<5;j++){//pega travessa
                            if(i == 3 && j == 4){
                                nao_existe_travessa_livre = true;
                                contpilha = 4;
                            }
                            if(atracamento[i].travessa[j].pilha->tamanho < 5){
                                insere_pilha(atracamento[i].travessa[j].pilha,navio_descarregando.pilha3->ultimo->conteiner);
                                remove_pilha(navio_descarregando.pilha3, &navio_descarregando.pilha3->ultimo->conteiner);
                                if(navio_descarregando.pilha3->tamanho == 0){
                                    //Sai do for de procura por travessa
                                    j = 5;
                                    i = 4;
                                }
                            }
                        }
                    }
                }
            }
        }


        if(verifica_navio_descarregou(navio_descarregando) == true){//Se o navio descarregou por completo remove ele da fila
            remove_fila(fila1,&navio_descarregando);
        }
        //Descarrega navio da fila 2
        navio_descarregando = fila2->primeiro->navio;
        nao_existe_travessa_livre = false;
        for(int contpilha = 0;contpilha<4;contpilha++){//Escolhe PILHA DO NAVIO
            if(contpilha == 0){//caso pilha 1
                while(navio_descarregando.pilha1->tamanho != 0 && nao_existe_travessa_livre == false){//enquanto pilha nao acaba
                    for(int i = 0;i<4;i++){//Escolhe atracamento
                        for(int j = 0;j<5;j++){//pega travessa
                            if(i == 3 && j == 4){
                                nao_existe_travessa_livre = true;
                                contpilha = 4;
                            }
                            if(atracamento[i].travessa[j].pilha->tamanho < 5){
                                insere_pilha(atracamento[i].travessa[j].pilha,navio_descarregando.pilha1->ultimo->conteiner);
                                remove_pilha(navio_descarregando.pilha1, &navio_descarregando.pilha1->ultimo->conteiner);
                                if(navio_descarregando.pilha1->tamanho == 0){
                                    //Sai do for de procura por travessa
                                    j = 5;
                                    i = 4;
                                }
                            }
                        }
                    }
                }
            }else if(contpilha==1){
                nao_existe_travessa_livre = false;
                while(navio_descarregando.pilha2->tamanho != 0 && nao_existe_travessa_livre == false){//enquanto pilha nao acaba
                    for(int i = 0;i<4;i++){//Escolhe atracamento
                        for(int j = 0;j<5;j++){//pega travessa
                            if(i == 3 && j == 4){
                                nao_existe_travessa_livre = true;
                                contpilha = 4;
                            }
                            if(atracamento[i].travessa[j].pilha->tamanho < 5){
                                insere_pilha(atracamento[i].travessa[j].pilha,navio_descarregando.pilha2->ultimo->conteiner);
                                remove_pilha(navio_descarregando.pilha2, &navio_descarregando.pilha2->ultimo->conteiner);
                                if(navio_descarregando.pilha2->tamanho == 0){
                                    //Sai do for de procura por travessa
                                    j = 5;
                                    i = 4;
                                }
                            }
                        }
                    }
                }
            }else if(contpilha == 2){//Caso pilha 3
                nao_existe_travessa_livre = false;
                while(navio_descarregando.pilha3->tamanho != 0 && nao_existe_travessa_livre == false){//enquanto pilha nao acaba
                    for(int i = 0;i<4;i++){//Escolhe atracamento
                        for(int j = 0;j<5;j++){//pega travessa
                            if(i == 3 && j == 4){
                                nao_existe_travessa_livre = true;
                                contpilha = 4;
                            }
                            if(atracamento[i].travessa[j].pilha->tamanho < 5){
                                insere_pilha(atracamento[i].travessa[j].pilha,navio_descarregando.pilha3->ultimo->conteiner);
                                remove_pilha(navio_descarregando.pilha3, &navio_descarregando.pilha3->ultimo->conteiner);
                                if(navio_descarregando.pilha3->tamanho == 0){
                                    //Sai do for de procura por travessa
                                    j = 5;
                                    i = 4;
                                }
                            }
                        }
                    }
                }
            }else if(contpilha == 3){//caso pilha 4
                nao_existe_travessa_livre = false;
                while(navio_descarregando.pilha3->tamanho != 0 && nao_existe_travessa_livre == false){//enquanto pilha nao acaba
                    for(int i = 0;i<4;i++){//Escolhe atracamento
                        for(int j = 0;j<5;j++){//pega travessa
                            if(i == 3 && j == 4){
                                nao_existe_travessa_livre = true;
                                contpilha = 4;
                            }
                            if(atracamento[i].travessa[j].pilha->tamanho < 5){
                                insere_pilha(atracamento[i].travessa[j].pilha,navio_descarregando.pilha3->ultimo->conteiner);
                                remove_pilha(navio_descarregando.pilha3, &navio_descarregando.pilha3->ultimo->conteiner);
                                if(navio_descarregando.pilha3->tamanho == 0){
                                    //Sai do for de procura por travessa
                                    j = 5;
                                    i = 4;
                                }
                            }
                        }
                    }
                }
            }
        }

        if(verifica_navio_descarregou(navio_descarregando) == true){//Se o navio descarregou por completo remove ele da fila
            remove_fila(fila2,&navio_descarregando);
        }
        //Descarrega navio da fila 3
        navio_descarregando = fila3->primeiro->navio;
        nao_existe_travessa_livre = false;
        for(int contpilha = 0;contpilha<4;contpilha++){//Escolhe PILHA DO NAVIO
            if(contpilha == 0){//caso pilha 1
                while(navio_descarregando.pilha1->tamanho != 0 && nao_existe_travessa_livre == false){//enquanto pilha nao acaba
                    for(int i = 0;i<4;i++){//Escolhe atracamento
                        for(int j = 0;j<5;j++){//pega travessa
                            if(i == 3 && j == 4){
                                nao_existe_travessa_livre = true;
                                contpilha = 4;
                            }
                            if(atracamento[i].travessa[j].pilha->tamanho < 5){
                                insere_pilha(atracamento[i].travessa[j].pilha,navio_descarregando.pilha1->ultimo->conteiner);
                                remove_pilha(navio_descarregando.pilha1, &navio_descarregando.pilha1->ultimo->conteiner);
                                if(navio_descarregando.pilha1->tamanho == 0){
                                    //Sai do for de procura por travessa
                                    j = 5;
                                    i = 4;
                                }
                            }
                        }
                    }
                }
            }else if(contpilha==1){
                nao_existe_travessa_livre = false;
                while(navio_descarregando.pilha2->tamanho != 0 && nao_existe_travessa_livre == false){//enquanto pilha nao acaba
                    for(int i = 0;i<4;i++){//Escolhe atracamento
                        for(int j = 0;j<5;j++){//pega travessa
                            if(i == 3 && j == 4){
                                nao_existe_travessa_livre = true;
                                contpilha = 4;
                            }
                            if(atracamento[i].travessa[j].pilha->tamanho < 5){
                                insere_pilha(atracamento[i].travessa[j].pilha,navio_descarregando.pilha2->ultimo->conteiner);
                                remove_pilha(navio_descarregando.pilha2, &navio_descarregando.pilha2->ultimo->conteiner);
                                if(navio_descarregando.pilha2->tamanho == 0){
                                    //Sai do for de procura por travessa
                                    j = 5;
                                    i = 4;
                                }
                            }
                        }
                    }
                }
            }else if(contpilha == 2){//Caso pilha 3
                nao_existe_travessa_livre = false;
                while(navio_descarregando.pilha3->tamanho != 0 && nao_existe_travessa_livre == false){//enquanto pilha nao acaba
                    for(int i = 0;i<4;i++){//Escolhe atracamento
                        for(int j = 0;j<5;j++){//pega travessa
                            if(i == 3 && j == 4){
                                nao_existe_travessa_livre = true;
                                contpilha = 4;
                            }
                            if(atracamento[i].travessa[j].pilha->tamanho < 5){
                                insere_pilha(atracamento[i].travessa[j].pilha,navio_descarregando.pilha3->ultimo->conteiner);
                                remove_pilha(navio_descarregando.pilha3, &navio_descarregando.pilha3->ultimo->conteiner);
                                if(navio_descarregando.pilha3->tamanho == 0){
                                    //Sai do for de procura por travessa
                                    j = 5;
                                    i = 4;
                                }
                            }
                        }
                    }
                }
            }else if(contpilha == 3){//caso pilha 4
                nao_existe_travessa_livre = false;
                while(navio_descarregando.pilha3->tamanho != 0 && nao_existe_travessa_livre == false){//enquanto pilha nao acaba
                    for(int i = 0;i<4;i++){//Escolhe atracamento
                        for(int j = 0;j<5;j++){//pega travessa
                            if(i == 3 && j == 4){
                                nao_existe_travessa_livre = true;
                                contpilha = 4;
                            }
                            if(atracamento[i].travessa[j].pilha->tamanho < 5){
                                insere_pilha(atracamento[i].travessa[j].pilha,navio_descarregando.pilha3->ultimo->conteiner);
                                remove_pilha(navio_descarregando.pilha3, &navio_descarregando.pilha3->ultimo->conteiner);
                                if(navio_descarregando.pilha3->tamanho == 0){
                                    //Sai do for de procura por travessa
                                    j = 5;
                                    i = 4;
                                }
                            }
                        }
                    }
                }
            }
        }
        if(verifica_navio_descarregou(navio_descarregando) == true){//Se o navio descarregou por completo remove ele da fila
            remove_fila(fila3,&navio_descarregando);
        }
        //Descarrega navio da fila 4
        navio_descarregando = fila4->primeiro->navio;
        nao_existe_travessa_livre = false;
        for(int contpilha = 0;contpilha<4;contpilha++){//Escolhe PILHA DO NAVIO
            if(contpilha == 0){//caso pilha 1
                while(navio_descarregando.pilha1->tamanho != 0 && nao_existe_travessa_livre == false){//enquanto pilha nao acaba
                    for(int i = 0;i<4;i++){//Escolhe atracamento
                        for(int j = 0;j<5;j++){//pega travessa
                            if(i == 3 && j == 4){
                                nao_existe_travessa_livre = true;
                                contpilha = 4;
                            }
                            if(atracamento[i].travessa[j].pilha->tamanho < 5){
                                insere_pilha(atracamento[i].travessa[j].pilha,navio_descarregando.pilha1->ultimo->conteiner);
                                remove_pilha(navio_descarregando.pilha1, &navio_descarregando.pilha1->ultimo->conteiner);
                                if(navio_descarregando.pilha1->tamanho == 0){
                                    //Sai do for de procura por travessa
                                    j = 5;
                                    i = 4;
                                }
                            }
                        }
                    }
                }
            }else if(contpilha==1){
                nao_existe_travessa_livre = false;
                while(navio_descarregando.pilha2->tamanho != 0 && nao_existe_travessa_livre == false){//enquanto pilha nao acaba
                    for(int i = 0;i<4;i++){//Escolhe atracamento
                        for(int j = 0;j<5;j++){//pega travessa
                            if(i == 3 && j == 4){
                                nao_existe_travessa_livre = true;
                                contpilha = 4;
                            }
                            if(atracamento[i].travessa[j].pilha->tamanho < 5){
                                insere_pilha(atracamento[i].travessa[j].pilha,navio_descarregando.pilha2->ultimo->conteiner);
                                remove_pilha(navio_descarregando.pilha2, &navio_descarregando.pilha2->ultimo->conteiner);
                                if(navio_descarregando.pilha2->tamanho == 0){
                                    //Sai do for de procura por travessa
                                    j = 5;
                                    i = 4;
                                }
                            }
                        }
                    }
                }
            }else if(contpilha == 2){//Caso pilha 3
                nao_existe_travessa_livre = false;
                while(navio_descarregando.pilha3->tamanho != 0 && nao_existe_travessa_livre == false){//enquanto pilha nao acaba
                    for(int i = 0;i<4;i++){//Escolhe atracamento
                        for(int j = 0;j<5;j++){//pega travessa
                            if(i == 3 && j == 4){
                                nao_existe_travessa_livre = true;
                                contpilha = 4;
                            }
                            if(atracamento[i].travessa[j].pilha->tamanho < 5){
                                insere_pilha(atracamento[i].travessa[j].pilha,navio_descarregando.pilha3->ultimo->conteiner);
                                remove_pilha(navio_descarregando.pilha3, &navio_descarregando.pilha3->ultimo->conteiner);
                                if(navio_descarregando.pilha3->tamanho == 0){
                                    //Sai do for de procura por travessa
                                    j = 5;
                                    i = 4;
                                }
                            }
                        }
                    }
                }
            }else if(contpilha == 3){//caso pilha 4
                nao_existe_travessa_livre = false;
                while(navio_descarregando.pilha3->tamanho != 0 && nao_existe_travessa_livre == false){//enquanto pilha nao acaba
                    for(int i = 0;i<4;i++){//Escolhe atracamento
                        for(int j = 0;j<5;j++){//pega travessa
                            if(i == 3 && j == 4){
                                nao_existe_travessa_livre = true;
                                contpilha = 4;
                            }
                            if(atracamento[i].travessa[j].pilha->tamanho < 5){
                                insere_pilha(atracamento[i].travessa[j].pilha,navio_descarregando.pilha3->ultimo->conteiner);
                                remove_pilha(navio_descarregando.pilha3, &navio_descarregando.pilha3->ultimo->conteiner);
                                if(navio_descarregando.pilha3->tamanho == 0){
                                    //Sai do for de procura por travessa
                                    j = 5;
                                    i = 4;
                                }
                            }
                        }
                    }
                }
            }
        }
        if(verifica_navio_descarregou(navio_descarregando) == true){//Se o navio descarregou por completo remove ele da fila
            remove_fila(fila4,&navio_descarregando);
        }
        //RELATORIO ATUAL
        printw("==ID's dos navios da fila 1==\n");
        mostra_fila(fila1);//Navios na fila 1
        printw("==ID's dos navios da fila 2==\n");
        mostra_fila(fila2);//Navios na fila 2
        printw("==ID's dos navios da fila 3==\n");
        mostra_fila(fila3);//Navios na fila 3
        printw("==ID's dos navios da fila 4==\n");
        mostra_fila(fila4);//Navios na fila 4
        c = getch();
        printw("Pressione ESC para sair\n");
        refresh();
    }while(c != 27);
    endwin();
    return 0;
}