#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Arvore.h"

char candidato1Char[50] = "Jair Messias Bolsonaro";
char candidato2Char[50] = "Luis Inacio Lula da Silva";

int candidato1=0, candidato2=0;

void limpaArvore(No *node) {
    if (node == NULL) return;

    limpaArvore(node->esq);
    limpaArvore(node->dir);

    free(node);
}

void criarArvore(No **no) {
    *no = NULL;
}

void contaVotos(No *no){

    if (no != NULL) {
        if(no->info->voto == 1) candidato1++;
        else candidato2++;

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

void mostraMenu() {
    int op, voto;
    Info *iAux;

    printf("\b==========Menu==========\n");
    printf("\b1 - Cadastrar um titulo\n");
    printf("\b2 - Apagar um titulo\n");
    printf("\b3 - Iniciar nova votacao\n");
    printf("\b4 - Votar\n");
    printf("\b5 - Retirar voto\n");
    printf("\b6 - Mostrar resultado parcial\n");
    printf("\b7 - Listar eleitores\n");
    printf("\b8 - Parar o programa\n");
    printf("\b9 - Imprimir arvore\n");
    printf("\b========================\n\n");

    printf("Digite sua opcao: ");
    do {
        scanf("%d", &op);
        if(op < 0 || op > 9) printf("\bOpcao invalida, digite novamente\n");
    } while (op < 0 || op > 9);

    printf("\n");

    switch (op) {
        case 1:
            criaInfo();
            break;
        case 2:
            printf("\bQual titulo deseja remover?\n");
            scanf("%d", &op);
            if(pesquisaTitulo(arvoreTitulos, op)){
                iAux = pesquisaTitulo(arvoreTitulos, op);
                retira(&arvoreTitulos, *iAux);
            } else{
                printf("\bTitulo nao existe\n\n");
            }
            break;
        case 3:
            printf("\bJa houve alguma votacao? (1- sim / 2- nao)\n");
            do {
                scanf("%d", &op);
                if (op < 1 || op > 2) printf("\bOpcao invalida\n");
            } while (op < 1 || op > 2);

            if (op == 1) {
                limpaArvore(arvoreVotos);
                criarArvore(&arvoreVotos);
            } else{
                criarArvore(&arvoreVotos);
            }
            break;
        case 4:
            printf("\bDigite seu titulo de eleitor: ");
            scanf("%d", &op);
            if (pesquisaTitulo(arvoreTitulos, op)) {
                if (!pesquisaTitulo(arvoreVotos, op)) {
                    printf("\bDigite seu voto:\n");
                    printf("\b1- %s\n", candidato1Char);
                    printf("\b2- %s\n", candidato2Char);
                    do {
                        scanf("%d", &voto);
                        if (voto < 1 || voto > 2) printf("\bVoto invalido!\n");
                    } while (voto < 1 || voto > 2);

                    iAux = pesquisaTitulo(arvoreTitulos, op);
                    iAux->voto = voto;
                    votar(iAux);
                }
            }else{
                printf("\b\nEleitor nao cadastrado\n");
            }
            break;
        case 5:
            printf("\bDigite o titulo do eleitor: \n");
            scanf("%d", &op);
            if(pesquisaTitulo(arvoreVotos, op)){
                iAux = pesquisaTitulo(arvoreVotos, op);
                retira(&arvoreVotos, *iAux);
            } else printf("\bEleitor nao votou ainda\n");
            break;
        case 6:
            printf("\b========================\n\n");
            printf("\bLista de votados:\n");
            contaVotos(arvoreVotos);
            printf("\b\n========Contagem========\n");
            if(candidato1 > candidato2){
                printf("\bCandidato 2 recebeu: %d votos\n", candidato2);
                printf("\bCandidato 1 recebeu: %d votos\n", candidato1);
                printf("\bO candidato %s venceu\n", candidato1Char);
            }
            else if(candidato2 < candidato1){
                printf("\bCandidato 1 recebeu: %d votos\n", candidato1);
                printf("\bCandidato 2 recebeu: %d votos\n", candidato2);
                printf("\bO candidato %s venceu\n", candidato2Char);
            }
            else printf("\bHouve um empate! Realize uma nova votacao\n");
            break;
        case 7:
            preOrderRec(arvoreVotos);
            break;
        case 8:
            limpaArvore(arvoreVotos);
            limpaArvore(arvoreTitulos);
            exit(1);
        default:
            mostraMenu();
    }
    mostraMenu();
}

Info *pesquisaTitulo(No *no, int titulo) {
    Info *iAux;

    if (no == NULL) return 0;

    if (titulo < no->info->titulo_eleitor) return pesquisaTitulo(no->esq, titulo);

    if (titulo > no->info->titulo_eleitor) return pesquisaTitulo(no->dir, titulo);

    iAux = no->info;
    return iAux;
}

void votar(Info *info) {
    insereTitulo(&arvoreVotos, info);
    printf("\bVoto contabilizado!\n");
}

int pesquisa(No *no, Info *info) {
    if (no == NULL) return 0;

    if (info->titulo_eleitor < no->info->titulo_eleitor) return pesquisa(no->esq, info);

    if (info->titulo_eleitor > no->info->titulo_eleitor) return pesquisa(no->dir, info);

    info = no->info;
    return 1;
}

void criaInfo() {
    Info *info;
    info = (Info *) malloc(sizeof(Info));

    printf("\bDigite o nome do eleitor: ");
    fflush(stdin);
    fgets(info->Nome, 50, stdin);
    do {
        printf("\bAgora, o numero do seu titulo: ");
        scanf("%d", &info->titulo_eleitor);

        if (info->titulo_eleitor <= 0 || strlen(info->Nome) <= 2) {
            printf("\bTitulo invalido\n");
            info->titulo_eleitor = -1;
        }
        if (pesquisa(arvoreTitulos, info)) {
            printf("\bTitulo ja existente, corrija o numero\n");
            info->titulo_eleitor = -1;
        }
    } while (info->titulo_eleitor <= 0);

    printf("\b\nEleitor criado com sucesso!\n\n");
    insereTitulo(&arvoreTitulos, info);
    mostraMenu();
}

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

void sucessor(No *q, No **r) {
    No *pAux;

    if ((*r)->esq != NULL) {
        sucessor(q, &(*r)->esq);
        return;
    }

    q->info = (*r)->info;
    pAux = *r;
    *r = (*r)->dir;
    free(pAux);
}

int retira(No **p, Info x) {
    No *pAux;
    if (*p == NULL) return 0;

    if (x.titulo_eleitor < (*p)->info->titulo_eleitor) return retira(&(*p)->esq, x);

    if (x.titulo_eleitor > (*p)->info->titulo_eleitor) return retira(&(*p)->dir, x);

    if ((*p)->dir == NULL) {
        pAux = *p;
        *p = (*p)->esq;
        free(pAux);
        mostraMenu();
        return 1;
    }
    if ((*p)->esq == NULL) {
        pAux = *p;
        *p = (*p)->dir;
        free(pAux);
        mostraMenu();
        return 1;
    }
    sucessor(*p, &(*p)->dir);

    mostraMenu();
    return 1;
}