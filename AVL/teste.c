#include <stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include "AVL.h"

int main(void){
    int quant1;
    AVL *T1 = avl_criar();

    printf("Insira a quantidade de elementos no T1: ");
    scanf("%d", &quant1);

    printf("Insira os elementos do T1: ");
    for(int i = 0; i < quant1; i++){
        int aux;

        scanf("%d", &aux);
        avl_inserir(T1, aux);
        avl_imprimir(T1);
    }

    printf("Insira a quantidade de elementos a serem removidos do T1: ");
    scanf("%d", &quant1);

    printf("Insira os elementos a serem removidos do T1: ");
    for(int i = 0; i < quant1; i++){
        int aux;

        scanf("%d", &aux);
        bool aux2 = avl_remover(T1, aux);
        avl_imprimir(T1);

    }

    int chaveBusca;
    printf("Insira a chave a ser buscada no T1: ");
    scanf("%d", &chaveBusca);
    int aux3 = avl_busca(T1, chaveBusca);
    if(aux3 != 0) printf("Chave encontrada\n");
    else printf("Chave nao encontrada\n");

    // ----------------------------------------------------------------

    int quant2;
    AVL *T2 = avl_criar();

    printf("Insira a quantidade de elementos no T2: ");
    scanf("%d", &quant2);

    printf("Insira os elementos do T2: ");
    for(int i = 0; i < quant2; i++){
        int aux;

        scanf("%d", &aux);
        avl_inserir(T2, aux);
        avl_imprimir(T2);
    }

    printf("Insira a quantidade de elementos a serem removidos do T2: ");
    scanf("%d", &quant2);

    printf("Insira os elementos a serem removidos do T2: ");
    for(int i = 0; i < quant2; i++){
        int aux;

        scanf("%d", &aux);
        bool aux2 = avl_remover(T2, aux);
        avl_imprimir(T2);

    }

    printf("Insira a chave a ser buscada no T2: ");
    scanf("%d", &chaveBusca);
    aux3 = avl_busca(T2, chaveBusca);
    if(aux3 != 0) printf("Chave encontrada\n");
    else printf("Chave nao encontrada\n");

    // ----------------------------------------------------------------

    printf("T1: ");
    avl_imprimir(T1);
    printf("T2: ");
    avl_imprimir(T2);

    printf("Uniao: ");
    AVL *TU = avl_uniao(T1, T2);
    avl_imprimir(TU);

    printf("Interseccao: ");
    AVL *TI = avl_interseccao(T1, T2);
    avl_imprimir(TI);

    avl_apagar(&T1);
    avl_apagar(&T2);

return 0;
}
