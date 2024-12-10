/*
Este código implementa um tipo abstrato de dado (TAD) chamado SET, que utiliza especificamente a Árvore Rubro-Negra (LLRBT) para representar os conjuntos. 
A Árvore Rubro-Negra é uma árvore binária de busca balanceada que garante operações eficientes (inserção, remoção e busca) com complexidade O(log n) no pior caso. 
*/

// Bibliotecas e TAD:
#include <stdio.h>
#include <stdlib.h>
#include "LLRBT.h"

#define RED 1 // Define que 'RED'=1.
#define BLACK 0 // Define que 'BLACK'=0.

// OBS: A cor da aresta entre um nó pai e um nó filho é ditada pela cor que está guardada no nó filho.

// Definição do tipo 'NO'.
typedef struct no_ NO;

struct no_{
    int chave; // Valor do nó.
    NO* esq; // Nó esquerdo.
    NO* dir; // Nó direito.
    int cor; // cor do nó.
};

// Definição do tipo 'LLRBT'.
struct llrbt{
    NO* raiz; // Raiz da árvore.
};

// função para criar uma árvore 'LLRBT'.
LLRBT* llrbt_criar(){
    // Aloca memória, checa a alocação e inicializa a árvore.
    LLRBT* aux=(LLRBT*)malloc(sizeof(LLRBT));

    if(aux!=NULL){
        aux->raiz=NULL;
    }else
        printf("Erro na alocação da LLRBT");

return aux;
}

// Função auxiliar que se utiliza do percurso 'pos-ordem' para apagar todos os nós de uma árvore. 
void apagar_no(NO** raiz){
    if(*raiz!=NULL){
        apagar_no(&(*raiz)->esq);
        apagar_no(&(*raiz)->dir);

        free(*raiz);
        *raiz=NULL;
    }
}

// Função principal que chama a função 'apagar_no' para apagar todos os nós e depois apaga a árvore.
void llrbt_apagar(LLRBT** T){
    if(*T!=NULL){
        if((*T)->raiz!=NULL){
            apagar_no(&(*T)->raiz);
        }
        free(*T);
        *T=NULL;
    }
}

// Função auxiliar para procurar um elemento dentro da árvore. Retorna 'true' caso encontre e 'false' se não.
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

// Função principal que realiza a chamada da função 'busca_aux" para procurar um elemento dentro da árvore.
bool llrbt_buscar(LLRBT* T, int chave){
    if(T!=NULL){
        return busca_aux(T->raiz, chave);
    }

return false;
}

// Função auxiliar que se utiliza do percurso 'em-ordem' para imprimir todos os nós de uma árvore em ordem crescente.
void imprimir_ordem(NO *raiz){
    if(raiz!=NULL){
        imprimir_ordem(raiz->esq);

        printf("%d, ", raiz->chave);

        imprimir_ordem(raiz->dir);
    }
}

// Função principal que realiza a chamada da função 'imprimir_ordem' para imprimir todos os nós da árvore.
void llrbt_imprimir(LLRBT* T){
    if(T!=NULL){
        imprimir_ordem(T->raiz);
        printf("\n");
    }else
        printf("ERRO: A Árvore não existe\n");
}

// Função auxiliar para inverter as cores de um nó e de seus filhos, caso existam.
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

// Função auxiliar para realizar a rotação para a direita de um nó e conserta as cores depois da rotação (balanceamento).
NO* rotacao_dir(NO* no){
    NO* aux=no->esq;

    no->esq=aux->dir;
    aux->dir=no;
    aux->cor=no->cor;
    no->cor=RED;

return aux;
}

// Função auxiliar para realizar a rotação para a esquerda de um nó e conserta as cores depois da rotação (balanceamento).
NO* rotacao_esq(NO* no){
    NO* aux=no->dir;

    no->dir=aux->esq;
    aux->esq=no;
    aux->cor=no->cor;
    no->cor=RED;

return aux;
}

// Função auxliar que retorna se um nó é vermelho ou não.
bool vermelho(NO* no){
    if(no!=NULL){
        return(no->cor==RED);
    }

return(false);
}

// Função auxiliar para criar um nó.
NO* cria_no_llrbt(int dado, int cor){
    // Aloca memória, verifica a alocação e inicializa o nó.
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

// Função auxiliar para inserir um nó já criado na sua posição correta. Após isso a função realiza o balanceamento da árvore, caso necessário.
NO* inserir_aux(NO* raiz, NO* novo){
    // Realiza a busca da posição correta do nó e o insere.
    if(raiz==NULL){
        raiz=novo;
    }else
    if(raiz->chave>novo->chave){
        raiz->esq=inserir_aux(raiz->esq, novo);
    }else
    if(raiz->chave<novo->chave){
        raiz->dir=inserir_aux(raiz->dir, novo);
    }

    // Realiza o rebalanceamento da árvore.
    if(vermelho(raiz->dir) && !vermelho(raiz->esq)){
        // Caso o nó equerdo seja preto e o direito vermelho realiza uma rotação para a esquerda.
        raiz=rotacao_esq(raiz);
    }
    if(vermelho(raiz->esq) && vermelho(raiz->esq->esq)){
        // Caso o nó esquerdo seja vermelho e o nó esquerdo do nó esquerdo seja também, realiza uma rotação para a direita.
        raiz=rotacao_dir(raiz);
    }
    if(vermelho(raiz->esq) && vermelho(raiz->dir)){
        // Caso o nó esquerdo e direito sejam vermelho inverte as cores.
        inverte(raiz);
    }

return raiz;
}

// Função principal para inserir um elemento na árvore.
bool llrbt_inserir(LLRBT* T, int chave){
    if(T!=NULL){
        NO* aux=cria_no_llrbt(chave, RED);

        if(aux!=NULL){
            T->raiz=inserir_aux(T->raiz, aux);
            T->raiz->cor=BLACK;
            return true;
        }
    }

return false;
}

// Função auxiliar para buscar o menor elemento de uma árvore.
int minimo(NO* no){
    while(no->esq!=NULL){
        no=no->esq;
    }

return no->chave;
}

// Função auxiliar para propagar aresta vermelha para a esquerda. 
NO* mov_ver_esq(NO* raiz){
    inverte(raiz);

    if(vermelho(raiz->dir->esq)){
        raiz->dir=rotacao_dir(raiz->dir);
        raiz=rotacao_esq(raiz);
        inverte(raiz);
    }

return raiz;
}

// Função auxiliar para propagar aresta vermelha para a direita.
NO* mov_ver_dir(NO* raiz){
    inverte(raiz);

    if(vermelho(raiz->esq->esq)){
        raiz=rotacao_dir(raiz);
        inverte(raiz);
    }

return raiz;
}

// Função auxiliar que apaga o menor nó de uma árvore se utilizando do conceito de propagação de arestas vermelhas.
NO* apaga_menor(NO** raiz){
    // Procura o nó e propaga arestas vermelhas para baixo.
    if((*raiz)->esq==NULL){
        free(*raiz);
        return NULL;
    }

    if(!vermelho((*raiz)->esq) && !vermelho((*raiz)->esq->esq)){
        //Propaga aresta vermelha para a esquerda.
        *raiz=mov_ver_esq(*raiz);
    }
    (*raiz)->esq=apaga_menor(&(*raiz)->esq);

    // Realiza o rebalanceamento da árvore.
    if(vermelho((*raiz)->dir) && !vermelho((*raiz)->esq)){
        // Caso o nó equerdo seja preto e o direito vermelho realiza uma rotação para a esquerda.
        *raiz=rotacao_esq(*raiz);
    }
    if(vermelho((*raiz)->esq) && vermelho((*raiz)->esq->esq)){
        // Caso o nó esquerdo seja vermelho e o nó esquerdo do nó esquerdo seja também, realiza uma rotação para a direita.
        *raiz=rotacao_dir(*raiz);
    }
    if(vermelho((*raiz)->esq) && vermelho((*raiz)->dir)){
        // Caso o nó esquerdo e direito sejam vermelho inverte as cores.
        inverte(*raiz);
    }

return *raiz;
}

// Função auxiliar que remove um nó de uma árove se utilizando do conceito de propagação de aresta vermelha.
NO* remover_aux(NO** raiz, int chave, bool* control){
    // Procura o nó e vai fazendo as propagações arestas vermelhas através de rotações e das funções 'mov_ver_esq' e 'mov_ver_dir'.
    if(*raiz==NULL){
        printf("O numero não esta na arvore\n");
        *control=false;
        return NULL;
    }
    if(chave<(*raiz)->chave){
        if(!vermelho((*raiz)->esq) && ((*raiz)->esq!=NULL && !vermelho((*raiz)->esq->esq))){
            // Propaga aresta vermelha para a esquerda.
            *raiz= mov_ver_esq(*raiz);
        }
        // Continua a procura na sub-árvore direita.
        (*raiz)->esq=remover_aux(&(*raiz)->esq, chave, control);
        
    }else{
        if(vermelho((*raiz)->esq)){
            // Rotaciona para a direita.
            *raiz=rotacao_dir(*raiz);
        }
        if(chave==(*raiz)->chave && (*raiz)->dir==NULL){ // Caso tenha encontrado o nó e ele não tem filho direito o nó pode apenas ser apagado.
            free(*raiz);
            return NULL;
        }
        if(!vermelho((*raiz)->dir) && ((*raiz)->dir!=NULL && !vermelho((*raiz)->dir->esq))){
            // Propaga aresta para a direita.
            *raiz=mov_ver_dir(*raiz);
        }
        if(chave==(*raiz)->chave){
            // Realiza a troca do nó que necessita ser apagado pelo menor da sub-árvore direita e depois apaga.
            (*raiz)->chave=minimo((*raiz)->dir);
            (*raiz)->dir=apaga_menor(&(*raiz)->dir);
        }else
            (*raiz)->dir=remover_aux(&(*raiz)->dir, chave, control);// Continua a procura na sub-árvore direita.
    }

    // Rebalanceia a árvore.
    if(vermelho((*raiz)->dir) && !vermelho((*raiz)->esq)){
        // Caso o nó equerdo seja preto e o direito vermelho realiza uma rotação para a esquerda.
        *raiz=rotacao_esq(*raiz);
    }
    if(vermelho((*raiz)->esq) && vermelho((*raiz)->esq->esq)){
        // Caso o nó esquerdo seja vermelho e o nó esquerdo do nó esquerdo seja também, realiza uma rotação para a direita.
        *raiz=rotacao_dir(*raiz);
    }
    if(vermelho((*raiz)->esq) && vermelho((*raiz)->dir)){
        // Caso o nó esquerdo e direito sejam vermelho inverte as cores.
        inverte(*raiz);
    }

return *raiz;
}

// Função principal para remover um elemento da árvore.
bool llrbt_remover(LLRBT* T, int chave){
    if(T!=NULL){
        bool control=true;
        T->raiz=remover_aux(&T->raiz, chave, &control);
        T->raiz->cor=BLACK;
        return control;
    }

return false;
}

/* ------------------------------ Funções Especificas ------------------------------ */

// Função auxiliar para inserir todos os nós de uma árvore em outra.
void uniao_aux(NO* no, LLRBT* B){
    if(no!=NULL){
        llrbt_inserir(B, no->chave);
        uniao_aux(no->esq, B);
        uniao_aux(no->dir, B);
    }
}

// Função principal para unir duas árvores passadas criando uma nova estrutura que será a união das duas. 
LLRBT* llrbt_uniao(LLRBT* T, LLRBT* C){
    if(T==NULL || C==NULL){
        return NULL;
    }

    LLRBT *aux=llrbt_criar();

    uniao_aux(T->raiz, aux);
    uniao_aux(C->raiz, aux);

return aux;
}

// Função auxiliar para inserir todos os elementos em comum de duas árvores em uma terceira.
void interseccao_aux(LLRBT* Maior, NO* Menor, LLRBT* novo){
    if(Menor==NULL){
        return;
    }

    if(llrbt_buscar(Maior, Menor->chave)){
        llrbt_inserir(novo, Menor->chave);
    }

    interseccao_aux(Maior, Menor->esq, novo);
    interseccao_aux(Maior, Menor->dir, novo);
}

// Função principal para realizar a intersecção de duas árvores criando uma nova estrutura para guardar esses elementos.
LLRBT* llrbt_interseccao(LLRBT* T, LLRBT* C){
    if(T==NULL || C==NULL){
        return NULL;
    }

    LLRBT* aux=llrbt_criar();

    interseccao_aux(T, C->raiz, aux);

return aux;
}