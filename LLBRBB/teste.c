#include <stdio.h>
#include<stdlib.h>
#include "LLRBT.h"

int main(void){
    int quant;
    LLRBT* T=llrbt_criar();

    scanf("%d", &quant);

    for(int i=0; i<quant; i++){
        int aux;

        scanf("%d", &aux);
        llrbt_inserir(T, aux);
        llrbt_imprimir(T);
    }

    scanf("%d", &quant);

    for(int i=0; i<quant; i++){
        int aux;

        scanf("%d", &aux);
        llrbt_remover(T, aux);
        llrbt_imprimir(T);
    }

    llrbt_apagar(&T);
    llrbt_imprimir(T);

return 0;
}
