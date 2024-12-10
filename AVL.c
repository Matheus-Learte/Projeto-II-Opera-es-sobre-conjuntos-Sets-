#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "AVL.h"

// Defnição do tipo 'NO'.
typedef struct no_ {
    int chave; // Valor do nó.
    struct no_ *esq; // Nó esquerdo.
    struct no_ *dir; // Nó direito.
    int FB; // Fator de Balanceamento.
} NO;

// Defnição do tipo 'AVL'.
typedef struct avl {
    NO *raiz; // Raiz da árvore.
    int profundidade; // Profundidade da árvore.
} AVL;

// Função para criar uma árvore AVL.
AVL *avl_criar(void){
    // Aloca memória e verifica a alocação, além de inicializar a árvore.
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

// Função auxiliar para fazer uma rotação direita (balaneamento).
NO *rot_dir(NO *a){
    NO *b = a->esq;
    a->esq = b->dir;
    b->dir = a;

    a->FB = b->FB = 0;

    return b;
}

// Função auxiliar para fazer uma rotação esquerda (balaneamento).
NO *rot_esq(NO *a){
    NO *b = a->dir;
    a->dir = b->esq;
    b->esq = a;

    a->FB = b->FB = 0;

    return b;
}

// Função auxiliar para fazer uma rotação esquerda-direita (balaneamento).
NO *rot_esqDir(NO *a){
    a->esq = rot_esq(a->esq);
    return rot_dir(a);
}

// Função auxiliar para fazer uma rotação direita-esquerda (balaneamento).
NO *rot_dirEsq(NO *a){
    a->dir = rot_dir(a->dir);
    return rot_esq(a);
}

/* ---------------------------------------------------------------------- */
 
// Função auxiliar para retornar a altura de um nó (usada para determinar o balancemento de um nó).
int altura_no(NO *no){
    if (no == NULL)
        return 0;
    
    // Recursivamente calcula as alturas das sub-árvores esquerda e direita.
    int altura_esq = altura_no(no->esq);
    int altura_dir = altura_no(no->dir);

    // A altura do nó é 1 + a maior altura das subárvores.
    if(altura_esq > altura_dir)
        return altura_esq + 1;
    else 
        return altura_dir + 1;
}

// Função auxiliar para criar um nó.
NO *cria_no(int chave){
    // Aloca memória e verifica a alocação, além de inicializar o nó.
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

// Função auxiliar para fazer a inserção do nó, já criado, na sua posição correta. Além de fazer o balanceamento da árvore.
NO *inserir_no(NO *raiz, int chave){
    // Busca a posição ideal para inserir o nó.
    if(raiz == NULL)
        raiz = cria_no(chave);
    else if(chave < raiz->chave)
        raiz->esq = inserir_no(raiz->esq, chave);
    else if(chave > raiz->chave)
        raiz->dir = inserir_no(raiz->dir, chave);
    else 
        return raiz;

    // Atualizar o fator de balanceamento.
    raiz->FB = ((altura_no(raiz->esq)) - (altura_no(raiz->dir)));

    // Realizar as rotações caso o fator de balanceamento seja 2 ou -2.
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

// Função para inserir um elemento na árvore.
bool avl_inserir(AVL *T, int chave){
    // Usa uma função auxiliar para poder fazer recurção.
    if(T != NULL)
        return(T->raiz = inserir_no(T->raiz, chave));
    printf("Erro na insercao do no.\n");
    return false;
}

// Função auxiliar para busca de um elemento.
bool avl_buscar_aux(NO *raiz, int chave){
    if(raiz == NULL) return false;

    if(raiz->chave == chave)
        return true;

    // Faz uso de recursão para buscar nas sub-árvores.
    if(raiz->chave > chave)
        return avl_buscar_aux(raiz->esq, chave);
    else if (raiz->chave < chave)
        return avl_buscar_aux(raiz->dir, chave);
}

// Função para buscar um elemento na árvore.
bool avl_buscar(AVL *T, int chave){
    // Usa uma função auxiliar para poder fazer recurção.
    if(T != NULL)
        return avl_buscar_aux(T->raiz, chave);
}

// Função auxiliar para fazer a troca de um elemento removido pelo maior número da sub-árvore esquerda desse elemento.
void troca_max_esq(NO *troca, NO *raiz, NO *anterior){
    // Busca o maior elemento da sub-árvore esquerda.
    if(troca->dir != NULL){
        troca_max_esq(troca->dir, raiz, troca);
        return;
    }

    // Faz a troca do elemento.
    if(raiz == anterior)
        anterior->esq = troca->esq;
    else
        anterior->dir =  troca->esq;
    
    // Libera o elemento removido.
    raiz->chave = troca->chave;
    free(troca);
    troca = NULL;
}

// Função auxiliar para remoção.
NO *avl_remover_aux(NO **raiz, int chave){ // Igual ABB
    if(*raiz==NULL){
        printf("No não encontrado\n");
        return NULL;
    }

    NO *aux;

    if(chave == (*raiz)->chave){
        // Caso 1 e 2: sem nós filhos ou só um nó filho; o tratamento é o mesmo.
        if((*raiz)->esq == NULL || (*raiz)->dir == NULL){
            aux = *raiz;

            if((*raiz)->esq == NULL)
                (*raiz) = (*raiz)->dir;
            else 
                (*raiz) = (*raiz)->esq;

            free(aux);
            aux = NULL;
        } else {
            // Caso 3: dois nós filhos. Encontra o maior elemento da sub-árvore esquerda e o substitui pelo elemento a ser removido.
            troca_max_esq((*raiz)->esq, (*raiz), (*raiz));
        }
    } else {
        // Busca do elemento a ser removido.
        if(chave < (*raiz)->chave)
            (*raiz)->esq = avl_remover_aux(&(*raiz)->esq, chave);
        else
            (*raiz)->dir = avl_remover_aux(&(*raiz)->dir, chave);
    }

    // Rebalanceia a árvore após a remoção do eleemento.
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

// Função para remover um elemento da árvore.
bool avl_remover(AVL *T, int chave){
    // Usa uma função auxiliar para poder fazer recurção.
    if(T != NULL)
        return(T->raiz = avl_remover_aux(&T->raiz, chave));
    printf("Erro na remocao do no.\n");
    return false;
}

// Função auxiliar para apagar os elementos da árvore.
void avl_apagar_aux(NO **raiz){
    if(*raiz != NULL){
        avl_apagar_aux(&(*raiz)->esq);
        avl_apagar_aux(&(*raiz)->dir);

        free(*raiz);
        *raiz = NULL;
    }
}

// Função para apagar a árvore.
void avl_apagar(AVL **T){
    // Usa uma função auxiliar para poder fazer recurção e apagar os elementos, em seguida libera a árvore.
    if(*T != NULL){
        avl_apagar_aux(&(*T)->raiz);
        free(*T);
        *T = NULL;
    } else if(*T == NULL)
        printf("Erro na liberacao da arvore.\n");
}

// Função auxiliar para imprimir os elementos da árvore de forma recursiva.
void avl_imprimir_aux(NO *raiz){
    if(raiz == NULL)
        return;

    avl_imprimir_aux(raiz->esq);
    printf("%d, ", raiz->chave);
    avl_imprimir_aux(raiz->dir); 
}

// Função para imprimir os elementos, em ordem crescente, da árvore.
void avl_imprimir(AVL *T){
    if(T != NULL){
        avl_imprimir_aux(T->raiz);
        printf("\n");
    }
}

/* ------------------------------ Funções Especificas ------------------------------ */

// Função auxiliar para fazer uso da recursão, ela insere os elementos numa nova aŕvore.
void avl_uniao_aux(NO *raiz, AVL *T){
    if(raiz != NULL){
        avl_inserir(T, raiz->chave);
        avl_uniao_aux(raiz->esq, T);
        avl_uniao_aux(raiz->dir, T);
    }
}

// Função para realizar a união de duas árvores.
AVL *avl_uniao(AVL *T1, AVL *T2){
    if(T2 == NULL)
        return T1;
    
    if(T1 != NULL){
        AVL *T3 = avl_criar();

        // Faz uso de uma função auxiliar recursivamente.
        avl_uniao_aux(T1->raiz, T3);
        avl_uniao_aux(T2->raiz, T3);

        return T3;
    }
    return NULL;
}

// Função auxiliar para fazer uso da recursão, ela insere os elementos em comum numa nova árvore.
void avl_interseccao_aux(AVL *Tmaior, NO *menor, AVL *novo){
    if(menor == NULL)
        return;

    if(avl_buscar(Tmaior, menor->chave))
        avl_inserir(novo, menor->chave);
    
    avl_interseccao_aux(Tmaior, menor->esq, novo);
    avl_interseccao_aux(Tmaior, menor->dir, novo);
}

// Função para realizar a intersecção de duas árvores.
AVL *avl_interseccao(AVL *T1, AVL *T2){
        if(T2 == NULL)
        return T1;
    
    if(T1 != NULL){
        AVL *T3 = avl_criar();

        avl_interseccao_aux(T1, T2->raiz, T3);

        return T3;
    }
    return NULL;
}