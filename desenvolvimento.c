#include "desenvolvimento.h"

enum bool{false = 0,true};//Enum para facilitar retorno de verdadeiro e falso

void incrementa_tempo_fila(Fila *fila){
    if(verifica_vazia_fila(fila) == false){
        Nodo *aux = fila->primeiro;
        while(aux != NULL){
            aux->navio.tempo++;
            aux = (Nodo*)aux->proximo;
        }
    }

}

void salva_id_txt(int id){
    //salva o id recebido no arquivo de texto para evitar repeticao de ids
    FILE *arquivo;
    arquivo = fopen("navio.txt","a+");
    fprintf(arquivo,"%d;",id);
    fclose(arquivo);
}
int gera_id_navio(){
    //gera um novo id com base no ultimo salvo no txt
    FILE *arquivo;
    arquivo = fopen("navio.txt","r");
    int ultimo_id = 0;
    while(!feof(arquivo)){
        fscanf(arquivo,"%d",&ultimo_id);//le o id
        getc(arquivo);//pula ;
        if(feof(arquivo)){//caso chegue no fil do arquivo sai do while
            break;
        }
    }
    ultimo_id++;//incrementa um no id 
    salva_id_txt(ultimo_id);//salva no txt
    return ultimo_id;//retorna id salvo
}

Navio gera_navio(){
    Navio navio;
    srand(time(NULL));
    navio.id = gera_id_navio();
    navio.tempo = 0;
    navio.quantidade_conteiners = (rand() % 12) + 4;//gera de 4 a 12 conteineres
    return navio;//retorna navio gerado
}
Conteiner gera_conteiner(){
    Conteiner conteiner;
    conteiner.valor = 1;
    return conteiner;//retorna conteiner gerado
}

void pilhas_navio(Navio navio){
    int pilha_atual = 1; 
    //coloca pelo menos um conteiner em cada pilha do navio
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
    //recebe a fila por referencia
    Navio navio = gera_navio();//gera um novo navio
    insere_fila(fila,navio);//chama funcao que coloca o navio na fila
    return navio;//retorna o ultimo navio inserido na determinada fila
}
void chama_veiculo_transporte(struct TRAVESSA travessa){
    for(int i = 0;i<5;i++){//for que repete 5 vezes indicando que liberara a pilha tida
        remove_pilha(travessa.pilha,&travessa.pilha->ultimo->conteiner);//Chama funcao para remover conteiner da pilha
    }
    travessa.pilha->tamanho = 0;//seta tamanho com 0 para garantir que o conteiner da travessa esta NULL
}
boolean verifica_navio_descarregou(Navio navio){
    if(navio.pilha1->tamanho == 0 && navio.pilha2->tamanho == 0 && navio.pilha3->tamanho == 0 && navio.pilha4->tamanho == 0){//caso todas as pilhas esteja zeradas indica que descarregou
        return true;//retorna true indicando que navio esta vazio
    }else{
        return false;//retorna false indicando que navio nao descarregou
    }
}

void descarrega_navio(struct ATRACAMENTO atracamento[], Fila *fila){
    Navio navio_descarregando = fila->primeiro->navio;
    int nao_existe_travessa_livre = false;
    if(verifica_vazia_fila(fila) == true){
        return; // caso a fila esteja vazia ja sai da funcao pois não tem navio para decarregar
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
    //Ao final do descarremento do navio verifica novamente se é necessário descarregar alguma travessa que esta cheia
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
}
