#include "../header/Arvore.h"
#include <stdio.h>
#include <stdlib.h>

//Declaração de variáveis globais responsáveis pelos candidatos
char candidato1Char[50] = "Jair Messias Bolsonaro";
char candidato2Char[50] = "Luis Inacio Lula da Silva";
int candidato1=0, candidato2=0;

//Função responsável pelo menu do programa e suas opções
void mostraMenu() {
    int op, voto;
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
                        printf("\b\nEleitor removido com sucesso!\n\n");
                    }
                } else{
                    printf("\bTitulo nao existe\n\n");
                }
                break;
                case 3:
                    printf("\bUma nova votacao excluirá dados anteriores,\n");
                    printf("\bdeseja continuar? (1 - sim / 2 - nao)\n");
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
                        mostraMenu();
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
                                if(candidato1 == 0 && candidato2 ==0){
                                    printf("\bAinda nao foi iniciada uma votacao.\n");
                                }
                                else{
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
                                }
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