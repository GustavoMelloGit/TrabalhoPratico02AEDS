#include "../header/Arvore.h"
#include <stdio.h>
#include <stdlib.h>

//Função responsável pelo menu do programa e suas opções
void mostraMenu() {
    int op, voto;
    static int votacaoIniciada = 0;
    Info *iAux;

    printf("\b\n==========Menu==========\n");
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
        if (op < 0 || op > 8) printf("\bOpcao invalida, digite novamente\n");
    } while (op < 0 || op > 8);

    printf("\n");

    switch (op) {
        case 1:
            criaInfo();
            break;
        case 2:
            printf("\bQual titulo deseja remover?\n");
            scanf("%d", &op);
            if (pesquisaTitulo(arvoreTitulos, op)) {
                iAux = pesquisaTitulo(arvoreTitulos, op);
                retira(&arvoreTitulos, *iAux);
                if (pesquisaTitulo(arvoreVotos, op)) {
                    iAux = pesquisaTitulo(arvoreVotos, op);
                    retira(&arvoreVotos, *iAux);
                }
                printf("\b\nEleitor removido com sucesso!\n\n");
            } else {
                printf("\bTitulo nao existe\n\n");
            }
            break;
        case 3:
            printf("\bUma nova votacao excluira dados anteriores,\n");
            printf("\bdeseja continuar? (1 - sim / 2 - nao)\n");
            do {
                scanf("%d", &op);
                if (op < 1 || op > 2) printf("\bOpcao invalida\n");
            } while (op < 1 || op > 2);

            if (op == 1) {
                limpaArvore(arvoreVotos);
                criarArvore(&arvoreVotos);
                limpaArvore(arvoreCandidatos);
                criarArvore(&arvoreCandidatos);
                votacaoIniciada = 1;
            } else {
                mostraMenu();
            }
            printf("\b\nVotacao iniciada!\n\n");
            break;
        case 4:
            //Verificação se uma votação foi criada
            if (votacaoIniciada == 0) {
                printf("\bVotacao ainda nao foi iniciada\n");
                mostraMenu();
            }
                //Votando
            else {
                printf("\bDigite seu titulo de eleitor: ");
                scanf("%d", &op);
                if (pesquisaTitulo(arvoreTitulos, op)) {
                    if (!pesquisaTitulo(arvoreVotos, op)) {
                        printf("\bDigite o titulo de eleitor de quem deseja votar: ");
                        do {
                            scanf("%d", &voto);
                            if (!contemTitulo(arvoreTitulos, voto)) printf("\bTitulo invalido! digite novamente: ");
                        } while (!contemTitulo(arvoreTitulos, voto));

                        iAux = pesquisaTitulo(arvoreTitulos, voto);
                        iAux->votoRecebido++;

                        iAux = pesquisaTitulo(arvoreTitulos, op);
                        iAux->voto = voto;
                        votar(iAux);
                        insereVoto(&arvoreCandidatos, pesquisaTitulo(arvoreTitulos, voto));
                    } else printf("\b\nEleitor ja votou!\n\n");
                } else printf("\b\nEleitor nao cadastrado\n");
            }

            break;
        case 5:
            printf("\bDigite seu titulo de eleitor: ");
            scanf("%d", &op);
            if (pesquisaTitulo(arvoreVotos, op)) {
                iAux = pesquisaTitulo(arvoreVotos, op);
                retira(&arvoreVotos, *iAux);
                iAux = pesquisaTitulo(arvoreTitulos, iAux->voto);
                iAux->votoRecebido--;
                insereVoto(&arvoreCandidatos, iAux);
            } else printf("\bEleitor nao votou ainda\n");
            break;
        case 6:
            imprimeVotos(arvoreCandidatos);
            break;
        case 7:
            preOrderRec(arvoreTitulos);
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