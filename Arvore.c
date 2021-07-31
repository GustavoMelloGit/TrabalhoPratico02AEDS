#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Arvore.h"

//Declaração de variáveis globais responsáveis pelos candidatos
char candidato1Char[50] = "Jair Messias Bolsonaro";
char candidato2Char[50] = "Luis Inacio Lula da Silva";
int candidato1=0, candidato2=0;


//Função responsável pelo menu do programa e suas opções
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
    printf("\b========================\n\n");

    printf("Digite sua opcao: ");
    do {
        scanf("%d", &op);
        if(op < 0 || op > 9) printf("\bOpcao invalida, digite novamente\n");
    } while (op < 0 || op > 8);

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
                if(pesquisaTitulo(arvoreVotos, op)){
                    iAux = pesquisaTitulo(arvoreVotos, op);
                    if(iAux->voto == 1) candidato1--;
                    else candidato2--;
                    retira(&arvoreVotos, *iAux);
                }
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
                candidato1 = 0;
                candidato2 = 0;
            } else{
                criarArvore(&arvoreVotos);
            }
            printf("\b\nVotacao iniciada!\n\n");
            break;
        case 4:
            printf("\bUma votacao ja foi criada? (1- sim / 2- nao)\n");
            do {
                scanf("%d", &op);
                if(op < 1 || op > 2) printf("\bOpcao Invalida, digite novamente: ");
            } while (op < 1 || op > 2);
            if(op == 2){
                printf("\bDeseja criar uma? (1- sim / 2- nao)\n");
                do {
                    scanf("%d", &op);
                    if(op < 1 || op > 2) printf("\bOpcao Invalida, digite novamente: ");
                } while (op < 1 || op > 2);

                if(op == 1){
                    limpaArvore(arvoreVotos);
                    criarArvore(&arvoreVotos);
                    printf("\b\nVotacao iniciada!\n\n");
                } else break;
            }
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

                    if(voto == 1) candidato1++;
                    else candidato2++;

                    iAux = pesquisaTitulo(arvoreTitulos, op);
                    iAux->voto = voto;
                    votar(iAux);
                }
            }else{
                printf("\b\nEleitor nao cadastrado\n");
            }
            break;
        case 5:
            printf("\bDigite o titulo do eleitor: ");
            scanf("%d", &op);
            if(pesquisaTitulo(arvoreVotos, op)){
                iAux = pesquisaTitulo(arvoreVotos, op);
                if(iAux->voto == 1) candidato1--;
                else candidato2--;
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
            else if(candidato2 > candidato1){
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

/* Função responsável por criar um eleitor e inserí-lo
 * na árvore de títulos */
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

//Função responsável por contabilizar os votos
void votar(Info *info) {
    insereTitulo(&arvoreVotos, info);
    printf("\bVoto contabilizado!\n");
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
