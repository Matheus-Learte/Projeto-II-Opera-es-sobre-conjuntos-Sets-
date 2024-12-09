#include <stdio.h>
#include<stdlib.h>
#include "LLRBT.h"

int main(void){
    int quant;
    LLRBT* T=llrbt_criar();
    LLRBT* C=llrbt_criar();

    scanf("%d", &quant);

    for(int i=0; i<quant; i++){
        int aux1, aux2;

        scanf("%d %d", &aux1, &aux2);
        llrbt_inserir(T, aux1);
        llrbt_inserir(C, aux2);
        llrbt_imprimir(T);
        llrbt_imprimir(C);
    }

    LLRBT* uniao=llrbt_uniao(T,C);
    LLRBT* inter=llrbt_interseccao(T,C);
    printf("UNIÃO: ");
    llrbt_imprimir(uniao);
    printf("INTER: ");
    llrbt_imprimir(inter);

    llrbt_apagar(&T);
    llrbt_apagar(&C);
    llrbt_apagar(&uniao);
    llrbt_apagar(&inter);

return 0;
}
