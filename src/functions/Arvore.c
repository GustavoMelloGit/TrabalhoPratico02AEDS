#include <stdlib.h>
#include <stdio.h>
#include "../header/Arvore.h"


//Cria a árvore para ser utilizada
void criarArvore(No **no) {
    *no = NULL;
}

//Libera todos os nós da árvore
void limpaArvore(No *node) {
    if (node == NULL) return;

    limpaArvore(node->esq);
    limpaArvore(node->dir);

    free(node);
}

//Realiza a contagem dos votos
void contaVotos(No *no){
    if (no != NULL) {
        printf("\b========================\n");
        printf("\bTitulo de eleitor: %d\n", no->info->titulo_eleitor);
        printf("\bNome: %s", no->info->Nome);
        if (no->info->voto == 1 || no->info->voto == 2) {
            printf("\bVoto: %d\n", no->info->voto);
        }
        contaVotos(no->esq);
        contaVotos(no->dir);
    }
}

//Função responsável por inserir um eleitor na árvore de títulos
void insereTitulo(No **no, Info *info) {
    if (*no == NULL) {
        *no = (No *) malloc(sizeof(No));
        (*no)->esq = NULL;
        (*no)->dir = NULL;
        (*no)->info = info;
    } else {
        if (info->titulo_eleitor < (*no)->info->titulo_eleitor) insereTitulo(&((*no)->esq), info);
        else insereTitulo(&((*no)->dir), info);
    }
}

//Função que percorre e imprime a árvore que a for enviada
void preOrderRec(No *no) {
    if (no != NULL) {
        printf("\b========================\n");
        printf("\bTitulo de eleitor: %d\n", no->info->titulo_eleitor);
        printf("\bNome: %s", no->info->Nome);
        if (no->info->voto == 1 || no->info->voto == 2) {
            printf("\bVoto: %d\n", no->info->voto);
        }
        preOrderRec(no->esq);
        preOrderRec(no->dir);
    }
}

//Função que procura o sucessor do nó a ser removido(caso ele tenha 2 filhos)
void sucessor(No *no, No **no2) {
    No *pAux;

    if ((*no2)->esq != NULL) {
        sucessor(no, &(*no2)->esq);
        return;
    }

    no->info = (*no2)->info;
    pAux = *no2;
    *no2 = (*no2)->dir;
    free(pAux);
}

/*Função que procura uma estrutura do tipo Info na
 * árvore e retorna true ou false, caso ela esteja
 * ou não incluída nela.*/
int pesquisa(No *no, Info *info) {
    if (no == NULL) return 0;

    if (info->titulo_eleitor < no->info->titulo_eleitor) return pesquisa(no->esq, info);

    if (info->titulo_eleitor > no->info->titulo_eleitor) return pesquisa(no->dir, info);

    info = no->info;
    return 1;
}

//Função que retira um nó da árvore
int retira(No **no, Info x) {
    No *pAux;
    if (*no == NULL) return 0;

    if (x.titulo_eleitor < (*no)->info->titulo_eleitor) return retira(&(*no)->esq, x);

    if (x.titulo_eleitor > (*no)->info->titulo_eleitor) return retira(&(*no)->dir, x);

    if ((*no)->dir == NULL) {
        pAux = *no;
        *no = (*no)->esq;
        free(pAux);
        mostraMenu();
        return 1;
    }
    if ((*no)->esq == NULL) {
        pAux = *no;
        *no = (*no)->dir;
        free(pAux);
        mostraMenu();
        return 1;
    }
    sucessor(*no, &(*no)->dir);

    mostraMenu();
    return 1;
}

//Função responsável por receber o número do título e devolver uma estrutura do tipo Info com aquele titulo
Info *pesquisaTitulo(No *no, int titulo) {
    Info *iAux;

    if (no == NULL) return 0;

    if (titulo < no->info->titulo_eleitor) return pesquisaTitulo(no->esq, titulo);

    if (titulo > no->info->titulo_eleitor) return pesquisaTitulo(no->dir, titulo);

    iAux = no->info;
    return iAux;
}