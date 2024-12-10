#include <stdio.h>
#include <stdlib.h>
#include "SET.h"

int main(void){
    SET *A, *B;
    int quant_a, quant_b, tipo, aux;

    scanf("%d", &tipo);/* 0=avl, 1=llrbt*/

    A=set_criar(tipo);
    B=set_criar(tipo);

    scanf("%d %d", &quant_a, &quant_b);

    for(int i=0; i< quant_a; i++){
        scanf("%d", &aux);
        set_inserir(A, aux);
    }

    for(int i=0; i<quant_b; i++){
        scanf("%d", &aux);
        set_inserir(B, aux);
    }

    int op;
    scanf("%d", &op);

    switch(op){
        case 1:{
            scanf("%d", &aux);

            if(set_pertence(A, aux)){
                printf("Pertence\n");
            }else
                printf("Não pertence\n");
        break;
        }
        case 2:{
            SET* uniao;

            if(quant_a>=quant_b){
                uniao=set_uniao(A, B);
            }else
                uniao=set_uniao(B,A);
            
            set_imprimir(uniao);
            set_apagar(&uniao);

        break;
        }
        case 3:{
            SET* interseccao;

            if(quant_a>=quant_b){
                interseccao=set_interseccao(A, B);
            }else
                interseccao=set_interseccao(B, A);

            set_imprimir(interseccao);
            set_apagar(&interseccao);

        break;
        }
        case 4:{
            scanf("%d", &aux);

            set_remover(A, aux);

            set_imprimir(A);
        }
    }

    set_apagar(&A);
    set_apagar(&B);

return 0;
}