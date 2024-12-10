 /*
 O cabeçalho de um módulo em C para manipulação de uma árvore AVL, que é uma árvore binária de busca balanceada:
 */ 

#ifndef _ARVORE_AVL_H
    #define _ARVORE_AVL_H

    typedef struct avl AVL; // Defnição do tipo 'AVL'.
    
    AVL *avl_criar(void); // Função para criar uma árvore AVL.
    bool avl_inserir (AVL *T, int chave); // Função para inserir um elemento na árvore.
    bool avl_busca(AVL *T, int chave); // Função para buscar um elemento na árvore.
    bool avl_remover(AVL *T, int chave); // Função para remover um elemento da árvore.
    void avl_imprimir (AVL *T); // Função para imprimir os elementos, em ordem crescente, da árvore.
    void avl_apagar(AVL **T); // Função para apagar a árvore.
    
    AVL *avl_uniao(AVL *T1, AVL *T2); // Função para realizar a união de duas árvores.
    AVL *avl_interseccao(AVL *T1, AVL *T2); // Função para realizar a intersecção de duas árvores.
 
#endif