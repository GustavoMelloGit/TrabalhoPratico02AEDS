#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Arvore.h"

void limpaArvore(No *node) {
    if (node == NULL) return;

    limpaArvore(node->esq);
    limpaArvore(node->dir);

    free(node);
}

void criarArvore(No **no) {
    *no = NULL;
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
                mostraMenu();
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
                mostraMenu();
            } else{
                criarArvore(&arvoreVotos);
                mostraMenu();
            }
            break;
        case 4:
            printf("\bDigite seu titulo de eleitor: ");
            scanf("%d", &op);
            if (pesquisaTitulo(arvoreTitulos, op)) {
                if (!pesquisaTitulo(arvoreVotos, op)) {
                    printf("\bDigite seu voto:\n");
                    printf("\b1- Jair Messias Bolsonaro\n");
                    printf("\b2- Luis Inacio Lula da Silva\n");
                    do {
                        scanf("%d", &voto);
                        if (voto < 1 || voto > 2) printf("\bVoto invalido!\n");
                    } while (voto < 1 || voto > 2);

                    iAux = pesquisaTitulo(arvoreTitulos, op);
                    iAux->voto = voto;
                    votar(iAux);
                    mostraMenu();
                }
            }else{
                printf("\b\nEleitor nao cadastrado\n");
                mostraMenu();
            }
            break;
        case 5:
            printf("\bDigite o titulo do eleitor: \n");
            scanf("%d", &op);
            if(pesquisaTitulo(arvoreVotos, op)){
                iAux = pesquisaTitulo(arvoreVotos, op);
                retira(&arvoreVotos, *iAux);
            } else printf("\bEleitor nao votou ainda\n");
            mostraMenu();
        case 8:
            limpaArvore(arvoreVotos);
            limpaArvore(arvoreTitulos);
            exit(1);
        case 9:
            printf("\bQual arvore deseja imprimir?\n");
            printf("\b1- Arvore de titulos\n");
            printf("\b2- Arvore de votos\n");
            do {
                scanf("%d", &op);
                if(op < 1 || op > 2) printf("\bOpcao invalida, digite novamente: ");
            } while (op < 1 || op > 2);

            if (op == 1) preOrderRec(arvoreTitulos);
            else preOrderRec(arvoreVotos);
        default:
            mostraMenu();
    }
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

    do {
        printf("\bDigite o nome do eleitor: ");
        fflush(stdin);
        fgets(info->Nome, 50, stdin);
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
    } else printf("\bNao a dados a serem impressos\n");
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
    /* Dois filhos */
    sucessor(*p, &(*p)->dir);

    mostraMenu();
    return 1;
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