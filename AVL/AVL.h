#ifndef _ARVORE_AVL_H
    #define _ARVORE_AVL_H

    typedef struct avl AVL;
    
    AVL *avl_criar(void);
    bool avl_inserir (AVL *avl, int chave);
    bool avl_remover(AVL *avl, int chave);
    void avl_imprimir (AVL *avl); // x
    void avl_apagar(AVL **avl);
 
#endif