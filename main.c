#include <stdio.h>
#include <stdlib.h>
#include "SET.h"

int main(void){
    SET *A, *B;
    int quant_a, quant_b, tipo, aux;

    scanf("%d", &tipo);

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

        }
        case 2:{

        }
        case 3:{

        }
        case 4:{
            
        }
    }

return 0;
}