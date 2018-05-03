#include "desenvolvimento.h"

enum bool{false = 0,true};//Enum para facilitar retorno de verdadeiro e falso


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
    for(int i = 0;i<5;i++){//for que repete 5 vezes indicando que liberara a pilha tida
        remove_pilha(travessa.pilha,&travessa.pilha->ultimo->conteiner);//Chama funcao para remover conteiner da pilha
    }
    travessa.pilha->tamanho = 0;//seta tamanho com 0 para garantir que o conteiner da travessa esta NULL
}
boolean verifica_navio_descarregou(Navio navio){
    if(navio.pilha1->tamanho == 0 && navio.pilha2->tamanho == 0 && navio.pilha3->tamanho == 0 && navio.pilha4->tamanho == 0){
        return true;
    }else{
        return false;
    }
}

void descarrega_navio(struct ATRACAMENTO atracamento[], Fila *fila){
    Navio navio_descarregando = fila->primeiro->navio;
    int nao_existe_travessa_livre = false;
    if(verifica_vazia_fila(fila) == true){
        return;
    }
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
                        while(atracamento[i].travessa[j].pilha->tamanho < 5 && navio_descarregando.pilha2->tamanho != 0){
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
                        while(atracamento[i].travessa[j].pilha->tamanho < 5 && navio_descarregando.pilha3->tamanho != 0){
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
            while(navio_descarregando.pilha4->tamanho != 0 && nao_existe_travessa_livre == false){//enquanto pilha nao acaba
                for(int i = 0;i<4;i++){//Escolhe atracamento
                    for(int j = 0;j<5;j++){//pega travessa
                        if(i == 3 && j == 4){
                            nao_existe_travessa_livre = true;
                            contpilha = 4;
                        }
                        while(atracamento[i].travessa[j].pilha->tamanho < 5 && navio_descarregando.pilha4->tamanho != 0){
                            insere_pilha(atracamento[i].travessa[j].pilha,navio_descarregando.pilha4->ultimo->conteiner);
                            remove_pilha(navio_descarregando.pilha4, &navio_descarregando.pilha4->ultimo->conteiner);
                            if(navio_descarregando.pilha4->tamanho == 0){
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
        remove_fila(fila,&navio_descarregando);
    }
}
