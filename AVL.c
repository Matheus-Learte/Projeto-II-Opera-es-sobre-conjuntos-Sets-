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
    AVL *T = (AVL*)malloc(sizeof(AVL));

    if(T!= NULL){
        T->raiz = NULL;
        T->profundidade = -1;
        return T;
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
    else 
        return raiz;

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

bool avl_inserir(AVL *T, int chave){
    if(T != NULL)
        return(T->raiz = inserir_no(T->raiz, chave));
    printf("Erro na insercao do no.\n");
    return false;
}

bool avl_busca_aux(NO *raiz, int chave){
    if(raiz == NULL) return false;

    if(raiz->chave == chave)
        return true;

    if(raiz->chave > chave)
        return avl_busca_aux(raiz->esq, chave);
    else if (raiz->chave < chave)
        return avl_busca_aux(raiz->dir, chave);
}

bool avl_busca(AVL *T, int chave){
    if(T != NULL)
        return avl_busca_aux(T->raiz, chave);
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
    if(*raiz==NULL){
        printf("NO não encontrado\n");
        return NULL;
    }

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

bool avl_remover(AVL *T, int chave){
    if(T != NULL)
        return(T->raiz = avl_remover_aux(&T->raiz, chave));
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

void avl_apagar(AVL **T){
    if(*T != NULL){
        avl_apagar_aux(&(*T)->raiz);
        free(*T);
        *T = NULL;
    } else if(*T == NULL)
        printf("Erro na liberacao da arvore.\n");
}

void avl_imprimir_aux(NO *raiz){
    if(raiz == NULL)
        return;

    avl_imprimir_aux(raiz->esq);
    printf("%d, ", raiz->chave);
    avl_imprimir_aux(raiz->dir); 
}

void avl_imprimir(AVL *T){
    if(T != NULL){
        avl_imprimir_aux(T->raiz);
        printf("\n");
    }
}

/* ------------------------------ Funções Especificas ------------------------------ */

void emOrdem(NO* raiz, int* array, int* index) {
    if (raiz != NULL) {
        emOrdem(raiz->esq, array, index);
        array[(*index)++] = raiz->chave;
        emOrdem(raiz->dir, array, index);
    }
}

int avl_contarNos(NO *raiz){
    if(raiz == NULL)
        return 0;
    return 1 + avl_contarNos(raiz->esq) + avl_contarNos(raiz->dir);
}

AVL *avl_uniao(AVL *T1, AVL *T2){
    if(T2 == NULL)
        return T1;
    
    if(T1 != NULL){
        AVL *T3 = avl_criar();

        int sizeT1 = avl_contarNos(T1->raiz);
        int sizeT2 = avl_contarNos(T2->raiz);

        int array1[sizeT1], array2[sizeT2], array3[sizeT1 + sizeT2];
        int index1 = 0, index2 = 0;

        emOrdem(T1->raiz, array1, &index1);
        emOrdem(T2->raiz, array2, &index2);

        for(int i = 0; i < sizeT1; i++){
            array3[i] = array1[i];
        }  

        for(int i = 0; i < sizeT2; i++){
            array3[sizeT1 + i] = array2[i];
        }

        for(int i = 0; i < sizeT1 + sizeT2; i++){
            bool aux = avl_inserir(T3, array3[i]);

            if(!aux)
                printf("Erro em avl_uniao.\n");
        }

        return T3;
    }
    return NULL;
}

AVL *avl_interseccao(AVL *T1, AVL *T2){
        if(T2 == NULL)
        return T1;
    
    if(T1 != NULL){
        AVL *T3 = avl_criar();

        int sizeT1 = avl_contarNos(T1->raiz);
        int sizeT2 = avl_contarNos(T2->raiz);

        int array1[sizeT1], array2[sizeT2], array3[sizeT1 + sizeT2];
        int index1 = 0, index2 = 0;

        emOrdem(T1->raiz, array1, &index1);
        emOrdem(T2->raiz, array2, &index2);

        int idx = 0;
        for(int i = 0; i < sizeT1; i++){
            for(int j = 0; j < sizeT2; j++){
                if(array1[i] == array2[j]){
                    array3[idx] = array1[i];
                    idx++;
                }
            }
        }  

        for(int i = 0; i < idx; i++){
            bool aux = avl_inserir(T3, array3[i]);

            if(!aux)
                printf("Erro em avl_uniao.\n");
        }

        return T3;
    }
    return NULL;
}