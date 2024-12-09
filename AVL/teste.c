#include <stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include "AVL.h"

int main(void){
    int quant;
    AVL* T = avl_criar();

    scanf("%d", &quant);

    for(int i = 0; i < quant; i++){
        int aux;

        scanf("%d", &aux);
        avl_inserir(T, aux);
        avl_imprimir(T);
    }

    scanf("%d", &quant);

    for(int i = 0; i < quant; i++){
        int aux;

        scanf("%d", &aux);
        bool aux2 = avl_remover(T, aux);
        printf("%d\n", aux2);
        avl_imprimir(T);

    }

    int chaveBusca;
    scanf("%d", &chaveBusca);
    int aux3 = avl_busca(T, chaveBusca);
    if(aux3 != 0) printf("Chave encontrada\n");

    avl_imprimir(T);
    avl_apagar(&T);

return 0;
}
