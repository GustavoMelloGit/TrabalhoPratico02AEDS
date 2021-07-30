#include <stdlib.h>
#include <stdio.h>
#include "Arvore.h"

void criarArvore(No **no){
    *no = NULL;
}

void criaInfo(){
    Info *info;
    info = (Info*) malloc(sizeof (Info));

    do{
        printf("Digite o nome do eleitor: ");
        fflush(stdin);
        fgets(info->Nome, 50, stdin);
        printf("Agora, o numero do seu titulo: ");
        scanf("%d", &info->titulo_eleitor);

        if(info->titulo_eleitor <= 0){
            printf("Titulo invalido\n");
        }
    } while (info->titulo_eleitor<=0);

    insereTitulo(&arvoreTitulos, info);

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