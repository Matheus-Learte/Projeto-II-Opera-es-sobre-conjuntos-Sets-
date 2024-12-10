#include <stdio.h>
#include <stdlib.h>
#include "SET.h"

struct set{
    AVL* avl;
    LLRBT* rubro;
    int tipo;
};

SET* set_criar(int tipo){
    if(tipo!= 0 && tipo!=1){
        printf("Tipo inválido");
        return NULL;
    }

    SET* aux=(SET*)malloc(sizeof(SET));

    if(aux!=NULL){
        aux->tipo=tipo;

        if(tipo==0){
            AVL* avl=avl_criar();

            if(avl!=NULL){
                aux->avl=avl;
            }else{
                printf("ERRO NA ALOCAÇÃO DA AVL\n");
                free(aux);
                return NULL;
            }
        }else{
            LLRBT* rubro=llrbt_criar();
            
            if(rubro!=NULL){
                aux->rubro=rubro;
            }else{
                free(aux);
                return NULL;
            }
        }
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
    }else
        printf("O SET não existe\n"); 
}

bool set_inserir(SET* C, int elemento){
    if(C!=NULL){
        if(C->tipo==0){
           return avl_inserir(C->avl, elemento);
        }else
           return llrbt_inserir(C->rubro, elemento);
    }else
       printf("O SET não existe\n"); 

return false;
}

SET* set_uniao(SET* A, SET *B){
    if(A!=NULL && B!=NULL){
        SET* uniao=set_criar(A->tipo);

        if(A->tipo==0){
            uniao->avl=avl_uniao(A->avl, B->avl);
        }else
            uniao->rubro=llrbt_uniao(A->rubro, B->rubro);

        return uniao;
    }

return NULL;
}

bool set_pertence(SET* A, int elemento){
    if(A!=NULL){
        if(A->tipo==0){
            return avl_buscar(A->avl, elemento);
        }else
            return llrbt_buscar(A->rubro, elemento);
    }else
        printf("O SET não existe\n");

return false;
}

bool set_remover(SET* C, int elemento){
    if(C!=NULL){
        if(C->tipo==0){
            return avl_remover(C->avl, elemento);
        }else
            return llrbt_remover(C->rubro, elemento);
    }else
        printf("O SET não existe\n"); 

return false;
}

void set_apagar(SET** C){
    if(C!=NULL){
        if((*C)->tipo==0){
            avl_apagar(&(*C)->avl);
        }else
            llrbt_apagar(&(*C)->rubro);

        *C=NULL;
    }
}

SET* set_interseccao(SET* A, SET* B){
    if(A!=NULL && B!=NULL){
        SET* interseccao=set_criar(A->tipo);

        if(A->tipo==0){
            interseccao->avl=avl_interseccao(A->avl, B->avl);
        }else
            interseccao->rubro=llrbt_interseccao(A->rubro, B->rubro);

        return interseccao;
    }

return NULL;
}

