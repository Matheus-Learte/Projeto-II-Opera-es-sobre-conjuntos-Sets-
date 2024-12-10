/*
O código implementa um tipo abstrato de dado (TAD) chamado SET, que permite a manipulação de conjuntos usando duas opções de árvores balanceadas: 
- AVL (Árvore Binária de Busca Balanceada); ou 
- LLRBT (Árvore Rubro-Negra)
*/

// Bibliotecas e TAD:
#include <stdio.h>
#include <stdlib.h>
#include "SET.h"

 // Defnição do tipo 'SET':
struct set{
    AVL* avl; // Árvore AVL.
    LLRBT* rubro; // Árvore Rubro-Negra.
    int tipo; // Tipo.
};

// Função para criar um conjunto.
SET* set_criar(int tipo){
    if(tipo!= 0 && tipo!=1){
        printf("Tipo inválido");
        return NULL;
    }

    // Aloca memória e verifica a alocação, além de inicializar o conjunto (sua árvore dependendo do tipo).
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

// Função que imprime os elementos do conjunto `C` (imprime a árvore de acordo com o tipo).
void set_imprimir(SET* C){
    if(C!=NULL){
        if(C->tipo==0){
            avl_imprimir(C->avl);
        }else
            llrbt_imprimir(C->rubro);
    }else
        printf("O SET não existe\n"); 
}

// Função que insere um elemento no conjunto `C` (insere em uma das árvores dependendo do tipo).
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

// Função que retorna a união de dois conjuntos `A` e `B` (dependendo do tipo, une duas avl's ou duas rubro-negra's).
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

// Função que verifica se um elemento pertence ao conjunto `A` (dependendo do tipo ele vai buscar o elemento em uma das árvores).
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

// Função que remove um elemento do conjunto `C` (remove de uma das árvores dependendo do tipo).
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

// Função que apaga (desaloca a memória de) o conjunto `C` (a árvore é escolhida de acordo com o tipo).
void set_apagar(SET** C){
    if(C!=NULL){
        if((*C)->tipo==0){
            avl_apagar(&(*C)->avl);
        }else
            llrbt_apagar(&(*C)->rubro);

        *C=NULL;
    }
}

// Função que retorna a interseção de dois conjuntos `A` e `B` (dependendo do tipo, intersecta duas avl's ou duas rubro-negra's).
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

