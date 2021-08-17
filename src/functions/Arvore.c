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
void contaVotos(No *no) {
    if (no != NULL) {
        printf("\b========================\n");
        printf("\bTitulo de eleitor: %d\n", no->info->titulo_eleitor);
        printf("\bNome: %s", no->info->Nome);
        printf("\bVoto: %d\n", no->info->voto);
        printf("\bVotos recebidos: %d\n", no->info->votoRecebido);

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

//Função responsável por inserir um voto na árvore de candidatos, verificando o Info já existe nela
void insereVoto(No **no, Info *info) {
    if (*no == NULL) {
        *no = (No *) malloc(sizeof(No));
        (*no)->esq = NULL;
        (*no)->dir = NULL;
        (*no)->info = info;
    } else {
        //Caso esteja na arvoreCandidatos, o votado deverá ser reinserido
        if (pesquisaTitulo(arvoreCandidatos, info->titulo_eleitor)) {
            Info *iAux;
            iAux = pesquisaTitulo(arvoreCandidatos, info->titulo_eleitor);

            //Retirando e reinserindo para que seja ordenado de forma correta na arvore
            if (iAux->votoRecebido == 0) {
                retira(&arvoreCandidatos, *iAux);
            } else {
                retira(&arvoreCandidatos, *iAux);
                insereVoto(&arvoreCandidatos, info);
            }
        } else {
            if (info->votoRecebido < (*no)->info->votoRecebido) insereVoto(&((*no)->esq), info);
            else insereVoto(&((*no)->dir), info);
        }
    }
}

//Função que imprime os votos recebidos de forma decrescente
void imprimeVotos(No *no) {
    if (no != NULL) {
        imprimeVotos(no->dir);
        printf("\b========================\n");
        printf("\bTitulo de eleitor: %d\n", no->info->titulo_eleitor);
        printf("\bNome: %s", no->info->Nome);
        printf("\bVotos recebidos: %d\n", no->info->votoRecebido);
        imprimeVotos(no->esq);
    }
}

//Função que percorre e imprime a árvore que a for enviada
void preOrderRec(No *no) {
    if (no != NULL) {
        printf("\b========================\n");
        printf("\bTitulo de eleitor: %d\n", no->info->titulo_eleitor);
        printf("\bNome: %s", no->info->Nome);

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
        return 1;
    }
    if ((*no)->esq == NULL) {
        pAux = *no;
        *no = (*no)->dir;
        free(pAux);
        return 1;
    }
    sucessor(*no, &(*no)->dir);

    return 1;
}

//Pesquisa se na árvore contém alguém com o título indicado e retorna verdadeiro ou falso
int contemTitulo(No *no, int titulo) {
    if (no == NULL) return 0;

    if (titulo < no->info->titulo_eleitor) return contemTitulo(no->esq, titulo);

    if (titulo > no->info->titulo_eleitor) return contemTitulo(no->dir, titulo);

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