#include <stdio.h>
#include <stdlib.h>
#include "SET.h"

struct set{
    AVL* avl;
    LLRBT* rubro;
    int tipo;
}


SET* set_criar(int tipo){
    if(tipo!= 0 && tipo!=1){
        printf("Tipo inválido");
        return NULL;
    }

    SET* aux=(SET*)malloc(sizeof(SET));

    if(aux!=NULL){
        aux->tipo=tipo;

        if(tipo==0){
            AVL* avl=alv_criar();

            if(avl!=NULL){
                aux->avl=avl;
            }else
                printf("ERRO NA ALOCAÇÃO DA AVL\n");
                free(aux);
                return NULL;
        }else
            LLRBT* rn=llrbt_criar();
            
            if(rn!=NULL){
                aux->rubro=rn;
            }else
                free(aux);
                return NULL;
    }else
        printf("Erro na alocação de memória para o SET\n");

return aux;
}

void set_imprimir(SET* C){
    if(C!=NULL){
        if(C->tipo==0){
            avl_imprimir(C->avl);
        }else
            llrbt_imprimir(C->rubro);
    }
}

bool set_inserir(SET* C, int elemento){
    if(C!=NULL){
        if(C->tipo==0){
           return avl_inserir(C->avl, elemento);
        }else
           return llrbt_inserir(C->rubro, elemento);
    }

return false;
}

SET* set_uniao(SET* A, SET *B){
    if(A!=NULL && B!=NULL){

    }

return NULL;
}

