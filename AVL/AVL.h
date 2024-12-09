#ifndef _ARVORE_AVL_H
    #define _ARVORE_AVL_H

    typedef struct avl AVL;
    
    AVL *avl_criar(void);
    bool avl_inserir (AVL *T, int chave);
    int avl_busca(AVL *T, int chave);
    bool avl_remover(AVL *T, int chave);
    void avl_imprimir (AVL *T); 
    void avl_apagar(AVL **T); 
    
    AVL *avl_uniao(AVL *T1, AVL *T2);
    AVL *avl_interseccao(AVL *T1, AVL *T2);
 
#endif