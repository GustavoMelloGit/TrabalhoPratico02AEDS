#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/Arvore.h"

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
        fflush(stdin);
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

