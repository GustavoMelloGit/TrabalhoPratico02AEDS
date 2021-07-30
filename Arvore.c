#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Arvore.h"


void criarArvore(No **no){
    *no = NULL;
}

void mostraMenu(){
    int op;

    printf("\b==========Menu==========\n");
    printf("\b1 - Cadastrar um titulo\n");
    printf("\b2 - Apagar um titulo\n");
    printf("\b3 - Iniciar nova votacao\n");
    printf("\b4 - Votar\n");
    printf("\b5 - Retirar voto\n");
    printf("\b6 - Imprimir arvore\n");
    printf("\b0 - Parar o programa\n");
    printf("\b========================\n\n");

    printf("Digite sua opcao: ");
    do {
        scanf("%d", &op);
    } while (op<0 || op>6);

    switch (op) {
        case 0:
            exit(1);
        case 1:
            criaInfo();
            break;
        case 6:
            printf("\bQual arvore deseja imprimir?\n");
            printf("\b1- Arvore de titulos\n");
            printf("\b1- Arvore de votos\n");
            do {
                scanf("%d", &op);
            } while (op<1 || op>2);

            if(op == 1) preOrderRec(arvoreTitulos);
            else preOrderRec(arvoreVotos);
    }
}

int pesquisa(No* no, Info *info) {
    if (no == NULL) return 0;

    if (info->titulo_eleitor < no->info->titulo_eleitor) return pesquisa(no->esq, info);

    if (info->titulo_eleitor > no->info->titulo_eleitor) return pesquisa (no->dir, info);

    return 1;
}

void criaInfo(){
    Info *info;
    info = (Info*) malloc(sizeof (Info));

    do{
        printf("\bDigite o nome do eleitor: ");
        fflush(stdin);
        fgets(info->Nome, 50, stdin);
        printf("\bAgora, o numero do seu titulo: ");
        scanf("%d", &info->titulo_eleitor);

        if(info->titulo_eleitor <= 0 || strlen(info->Nome) <= 2){
            printf("\bTitulo invalido\n");
            info->titulo_eleitor = -1;
        }
        if(pesquisa(arvoreTitulos, info)){
            printf("\bTitulo ja existente, corrija o numero\n");
            info->titulo_eleitor = -1;
        }
    } while (info->titulo_eleitor<=0);

    printf("\b\nEleitor criado com sucesso!\n\n");
    insereTitulo(&arvoreTitulos, info);
    mostraMenu();
}

void insereTitulo(No **no, Info *info){
    if(*no == NULL){
        *no = (No*) malloc(sizeof(No));
        (*no)->esq = NULL;
        (*no)->dir = NULL;
        (*no)->info = info;
    }
    else{
        if(info->titulo_eleitor < (*no)->info->titulo_eleitor) insereTitulo(&((*no)->esq), info);
        else insereTitulo(&((*no)->dir), info);
    }
}

void preOrderRec (No* no) {
    if(no != NULL) {
        printf("\b========================\n");
        printf ("\bTitulo de eleitor: %d\n", no->info->titulo_eleitor);
        printf("\bNome: %s", no->info->Nome);
        preOrderRec (no->esq);
        preOrderRec (no->dir);
    }
}

//void insercao(No **no, Info *info){
//    if (*no == NULL){
//        *no=(No *)malloc(sizeof (No));
//        (*no)->esq=NULL;
//        (*no)->dir=NULL;
//        (*no)->info = info;
//    }
//    else{
//        if (item.codigo < ((*no)->item.codigo)) insercao(&((*no)->esq), item);
//        else insercao(&((*no)->dir), item);
//    }
//}