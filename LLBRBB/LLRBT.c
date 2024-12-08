#include <stdio.h>
#include <stdlib.h>
#include "LLRBT.h"

#define RED 1
#define BLACK 0

typedef struct no_ NO;

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
            apagar_no(&(*T)->raiz);
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
        if(raiz->chave>chave){
            return busca_aux(raiz->esq, chave);
        }else
            return busca_aux(raiz->dir, chave);
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

        printf("%d ", raiz->chave);

        imprimir_ordem(raiz->dir);
    }
}

void llrbt_imprimir(LLRBT* T){
    if(T!=NULL){
        imprimir_ordem(T->raiz);
        printf("\n");
    }else
        printf("ERRO: A Árvore não existe\n");
}

void inverte(NO* no){
    if(no!=NULL){
        no->cor=!no->cor;

        if(no->esq!=NULL){
            no->esq->cor=!no->esq->cor;
        }
        if(no->dir!=NULL){
            no->dir->cor=!no->dir->cor;
        }
    }
}

NO* rotacao_dir(NO* no){
    NO* aux=no->esq;

    no->esq=aux->dir;
    aux->dir=no;
    aux->cor=no->cor;
    no->cor=RED;

return aux;
}

NO* rotacao_esq(NO* no){
    NO* aux=no->dir;

    no->dir=aux->esq;
    aux->esq=no;
    aux->cor=no->cor;
    no->cor=RED;

return aux;
}

bool vermelho(NO* no){
    if(no!=NULL){
        return(no->cor==RED);
    }

return(false);
}

NO* cria_no(int dado, int cor){
    NO* aux=(NO*)malloc(sizeof(NO));

    if(aux!=NULL){
        aux->chave=dado;
        aux->cor=cor;
        aux->esq=NULL;
        aux->dir=NULL;
    }else
        printf("Erro na alocação do NO");

return aux;
}

NO* inserir_aux(NO* raiz, NO* novo){
    if(raiz==NULL){
        raiz=novo;
    }else
    if(raiz->chave>novo->chave){
        raiz->esq=inserir_aux(raiz->esq, novo);
    }else
    if(raiz->chave<novo->chave){
        raiz->dir=inserir_aux(raiz->dir, novo);
    }

    if(vermelho(raiz->dir) && !vermelho(raiz->esq)){
        raiz=rotacao_esq(raiz);
    }
    if(vermelho(raiz->esq) && vermelho(raiz->esq->esq)){
        raiz=rotacao_dir(raiz);
    }
    if(vermelho(raiz->esq) && vermelho(raiz->dir)){
        inverte(raiz);
    }

return raiz;
}

bool llrbt_inserir(LLRBT* T, int chave){
    if(T!=NULL){
        NO* aux=cria_no(chave, RED);

        if(aux!=NULL){
            T->raiz=inserir_aux(T->raiz, aux);
            return true;
        }
    }

return false;
}

int minimo(NO* no){
    while(no->esq!=NULL){
        no=no->esq;
    }

return no->chave;
}

NO* mov_ver_esq(NO* raiz){
    inverte(raiz);

    if(vermelho(raiz->dir->esq)){
        raiz->dir=rotacao_dir(raiz->dir);
        raiz=rotacao_esq(raiz);
        inverte(raiz);
    }

return raiz;
}

NO* mov_ver_dir(NO* raiz){
    inverte(raiz);

    if(vermelho(raiz->esq->esq)){
        raiz=rotacao_dir(raiz);
        inverte(raiz);
    }

return raiz;
}

NO* apaga_menor(NO** raiz){
    if((*raiz)->esq==NULL){
        free(*raiz);
        return NULL;
    }

    if(!vermelho((*raiz)->esq) && !vermelho((*raiz)->esq->esq)){
        *raiz=mov_ver_esq(*raiz);
    }
    (*raiz)->esq=apaga_menor(&(*raiz)->esq);


    if(vermelho((*raiz)->dir) && !vermelho((*raiz)->esq)){
        *raiz=rotacao_esq(*raiz);
    }
    if(vermelho((*raiz)->esq) && vermelho((*raiz)->esq->esq)){
        *raiz=rotacao_dir(*raiz);
    }
    if(vermelho((*raiz)->esq) && vermelho((*raiz)->dir)){
        inverte(*raiz);
    }

return *raiz;
}

NO* remover_aux(NO** raiz, int chave, bool* control){
    if(*raiz==NULL){
        printf("O numero não esta na arvore\n");
        *control=false;
        return NULL;
    }
    if(chave<(*raiz)->chave){
        if(!vermelho((*raiz)->esq) && ((*raiz)->esq!=NULL && !vermelho((*raiz)->esq->esq))){
            *raiz= mov_ver_esq(*raiz);
        }
        (*raiz)->esq=remover_aux(&(*raiz)->esq, chave, control);
        
    }else{
        if(vermelho((*raiz)->esq)){
            *raiz=rotacao_dir(*raiz);
        }
        if(chave==(*raiz)->chave && (*raiz)->dir==NULL){
            free(*raiz);
            return NULL;
        }
        if(!vermelho((*raiz)->dir) && ((*raiz)->dir!=NULL && !vermelho((*raiz)->dir->esq))){
            *raiz=mov_ver_dir(*raiz);
        }
        if(chave==(*raiz)->chave){
            (*raiz)->chave=minimo((*raiz)->dir);
            (*raiz)->dir=apaga_menor(&(*raiz)->dir);
        }else
            (*raiz)->dir=remover_aux(&(*raiz)->dir, chave, control);
    }

    if(vermelho((*raiz)->dir) && !vermelho((*raiz)->esq)){
        *raiz=rotacao_esq(*raiz);
    }
    if(vermelho((*raiz)->esq) && vermelho((*raiz)->esq->esq)){
        *raiz=rotacao_dir(*raiz);
    }
    if(vermelho((*raiz)->esq) && vermelho((*raiz)->dir)){
        inverte(*raiz);
    }

return *raiz;
}

bool llrbt_remover(LLRBT* T, int chave){
    if(T!=NULL){
       bool control=true;
       T->raiz=remover_aux(&T->raiz, chave, &control);

        return control;
    }

return false;
}