/*
O programa implementa operações sobre conjuntos utilizando árvores balanceadas (AVL ou LLRBT). 
Ele permite ao usuário inserir elementos nos conjuntos, realizar operações de união, interseção, verificação de pertencimento e remoção de elementos, 
além de imprimir o resultado de cada operação. O código também se preocupa em liberar a memória ao final, evitando vazamentos de memória.
*/

// Bibliotecas e TAD:
#include <stdio.h>
#include <stdlib.h>
#include "SET.h"

// FUnção principal:
int main(void){
    // Declaração e inicialização dos conjuntos A e B.
    SET *A, *B;
    int quant_a, quant_b, tipo, aux;

    // Lê o tipo de árvore que será usada (0 = AVL, 1 = LLRBT).
    scanf("%d", &tipo);

    // Cria os conjuntos A e B usando a árvore escolhida.
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

    // Menu para escolher a operação desejada (1 = pertence, 2 = união, 3 = interseção, 4 = remover elemento).
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

    // Apaga os conjuntos A e B.
    set_apagar(&A);
    set_apagar(&B);

return 0;
}