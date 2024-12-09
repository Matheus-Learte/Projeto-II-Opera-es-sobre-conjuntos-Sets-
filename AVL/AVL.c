#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "AVL.h"

typedef struct no_ {
    int chave;
    struct no_ *esq;
    struct no_ *dir;
    int FB;
} NO;

typedef struct avl {
    NO *raiz;
    int profundidade;
    // ...
} AVL;

AVL *avl_criar(void){
    AVL *avl = (AVL*)malloc(sizeof(AVL));

    if(avl!= NULL){
        avl->raiz = NULL;
        avl->profundidade = -1;
        return avl;
    }

    printf("Erro na criacao da arvore.\n");
    return NULL;
}

/* ------------------------------ Rotações ------------------------------ */

NO *rot_dir(NO *a){
    NO *b = a->esq;
    a->esq = b->dir;
    b->dir = a;

    a->FB = b->FB = 0;

    return b;
}

NO *rot_esq(NO *a){
    NO *b = a->dir;
    a->dir = b->esq;
    b->esq = a;

    a->FB = b->FB = 0;

    return b;
}

NO *rot_esqDir(NO *a){
    a->esq = rot_esq(a->esq);
    return rot_dir(a);
}

NO *rot_dirEsq(NO *a){
    a->dir = rot_dir(a->dir);
    return rot_esq(a);
}

/* ---------------------------------------------------------------------- */

int altura_no(NO *no){
    if (no == NULL)
        return 0;
    
    // Recursivamente calcula as alturas das sub-árvores esquerda e direita
    int altura_esq = altura_no(no->esq);
    int altura_dir = altura_no(no->dir);

    // A altura do nó é 1 + a maior altura das subárvores
    if(altura_esq > altura_dir)
        return altura_esq + 1;
    else 
        return altura_dir + 1;
}

NO *cria_no(int chave){
    NO *newNode = (NO*)malloc(sizeof(NO));

    if(newNode!= NULL){
        newNode->chave = chave;
        newNode->esq = NULL;
        newNode->dir = NULL;
        newNode->FB = 0;

        return newNode;
    }

    printf("Erro na criacao do no.\n");
    return NULL;
}

NO *inserir_no(NO *raiz, int chave){
    if(raiz == NULL)
        raiz = cria_no(chave);
    else if(chave < raiz->chave)
        raiz->esq = inserir_no(raiz->esq, chave);
    else if(chave > raiz->chave)
        raiz->dir = inserir_no(raiz->dir, chave);

    // Atualizar o fator de balanceamento
    raiz->FB = ((altura_no(raiz->esq)) - (altura_no(raiz->dir)));

    if(raiz->FB == -2)
        if(raiz->dir->FB <= 0)
            raiz = rot_esq(raiz);
        else
            raiz = rot_dirEsq(raiz);
    else if(raiz->FB == 2)
        if(raiz->esq->FB >= 0)
            raiz = rot_dir(raiz);
        else
            raiz = rot_esqDir(raiz);

    return raiz;
}

bool avl_inserir(AVL *avl, int chave){
    if(avl != NULL)
        return(avl->raiz = inserir_no(avl->raiz, chave));
    printf("Erro na insercao do no.\n");
    return false;
}

int avl_busca_aux(NO *raiz, int chave){
    if(raiz == NULL) return 0;

    if(raiz->chave == chave)
        return chave;

    if(raiz->chave > chave)
        return avl_busca_aux(raiz->esq, chave);
    else if (raiz->chave < chave)
        return avl_busca_aux(raiz->dir, chave);
}

int avl_busca(AVL *avl, int chave){
    if(avl != NULL)
        printf("Chave nao encontrada.\n");
    return avl_busca_aux(avl->raiz, chave);
}

void troca_max_esq(NO *troca, NO *raiz, NO *anterior){
    if(troca->dir != NULL){
        troca_max_esq(troca->dir, raiz, troca);
        return;
    }

    if(raiz == anterior)
        anterior->esq = troca->esq;
    else
        anterior->dir =  troca->esq;
    
    raiz->chave = troca->chave;
    free(troca);
    troca = NULL;
}

NO *avl_remover_aux(NO **raiz, int chave){ // Igual ABB
    NO *aux;

    if(chave == (*raiz)->chave){
        if((*raiz)->esq == NULL || (*raiz)->dir == NULL){
            aux = *raiz;

            if((*raiz)->esq == NULL)
                (*raiz) = (*raiz)->dir;
            else 
                (*raiz) = (*raiz)->esq;

            free(aux);
            aux = NULL;
        } else {
            troca_max_esq((*raiz)->esq, (*raiz), (*raiz));
        }
    } else {
        if(chave < (*raiz)->chave)
            (*raiz)->esq = avl_remover_aux(&(*raiz)->esq, chave);
        else
            (*raiz)->dir = avl_remover_aux(&(*raiz)->dir, chave);
    }

    if(*raiz != NULL){
        (*raiz)->FB = altura_no((*raiz)->esq) - altura_no((*raiz)->dir);
    
        if((*raiz)->FB == 2){
            if((*raiz)->esq->FB >= 0)
                *raiz = rot_dir(*raiz);
            else
                *raiz = rot_esqDir(*raiz);
        }

        if((*raiz)->FB == -2){
            if((*raiz)->dir->FB <= 0)
                *raiz = rot_esq(*raiz);
            else
                *raiz = rot_dirEsq(*raiz);
        }
    }

    return *raiz;
}

bool avl_remover(AVL *avl, int chave){
    if(avl != NULL)
        return(avl->raiz = avl_remover_aux(&avl->raiz, chave));
    printf("Erro na remocao do no.\n");
    return false;
}

void avl_apagar_aux(NO **raiz){
    if(*raiz != NULL){
        avl_apagar_aux(&(*raiz)->esq);
        avl_apagar_aux(&(*raiz)->dir);

        free(*raiz);
        *raiz = NULL;
    }
}

void avl_apagar(AVL **avl){
    if(*avl != NULL){
        avl_apagar_aux(&(*avl)->raiz);
        free(*avl);
        *avl = NULL;
    } else if(*avl == NULL)
        printf("Erro na liberacao da arvore.\n");
}

void avl_imprimir_aux(NO *raiz){
    if(raiz == NULL)
        return;

    avl_imprimir_aux(raiz->esq);
    printf("%d ", raiz->chave);
    avl_imprimir_aux(raiz->dir); 
}

void avl_imprimir(AVL *avl){
    if(avl != NULL){
        avl_imprimir_aux(avl->raiz);
        printf("\n");
    }
}