#include <stdio.h>
#include <stdlib.h>
#include "LLRBT.h"

#define RED 1
#define BLACK 0

typedef no_ NO;

struct no_{
    int chave;
    NO* esq;
    NO* dir;
    int cor;
};

struct llrbt{
    NO* raiz;
};

LLRBT* llrbt_criar(){
    LLRBT* aux=(LLRBT*)malloc(sizeof(LLRBT));

    if(aux!=NULL){
        aux->raiz=NULL;
    }else
        printf("Erro na alocação da arvore");

return aux;
}

void apagar_no(NO** raiz){
    if(*raiz!=NULL){
        apagar_no(&(*raiz)->esq);
        apagar_no(&(*raiz)->dir);

        free(*raiz);
        *raiz=NULL;
    }
}

void llrbt_apagar(LLRBT** T){
    if(*T!=NULL){
        if((*T)->raiz!=NULL){
            apagar_no(&(*T)->raiz)
        }
        free(*T);
        *T=NULL;
    }
}

bool busca_aux(NO* raiz, int chave){
    if(raiz!=NULL){
        if(raiz->chave==chave){
            return true;
        }
        if(raiz->chave<chave){
            busca_aux(raiz->esq, chave);
        }else
            busca_aux(raiz->dir, chave);
    }

return false;
}

bool llrbt_buscar(LLRBT* T, int chave){
    if(T!=NULL){
        return busca_aux(T->raiz, chave);
    }

return false;
}

void imprimir_ordem(NO *raiz){
    if(raiz!=NULL){
        imprimir_ordem(raiz->esq);

        printf("%d", item_get_chave(raiz->item));

        imprimir_ordem(raiz->dir);
    }
}

void llrbt_imprimir(LLRBT* T){
    if(T!=NULL){
        imprimir_ordem(T->raiz);
    }else
        printf("ERRO: A Árvore não existe\n");
}